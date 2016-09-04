#include "modulations.h"

// constellation point tables (normalized or unit power and gray coding)
// PSK
gr_complex J_sqrt_2 = gr_complex(0,1/sqrt(2));
gr_complex _sqrt_2  = gr_complex(1/sqrt(2));
float _mag_ = 2/sqrt(10);

gr_complex PSK2[] = {_sqrt_2+J_sqrt_2, -(_sqrt_2+J_sqrt_2)};
gr_complex PSK4[] = {_sqrt_2+J_sqrt_2, -_sqrt_2+J_sqrt_2, -_sqrt_2-J_sqrt_2, _sqrt_2-J_sqrt_2};
gr_complex PSK8[] = {1,_sqrt_2+J_sqrt_2, -_sqrt_2+J_sqrt_2, gr_complex(0,1),
                     _sqrt_2-J_sqrt_2, gr_complex(0,-1), -1, -_sqrt_2-J_sqrt_2};
gr_complex PAM2[] = {-_sqrt_2, _sqrt_2};
gr_complex PAM4[] = {-1.5*4/sqrt(5.0),-0.5*4/sqrt(5.0),0.5*4/sqrt(5.0),1.5*4/sqrt(5.0)};
gr_complex PAM8[] = {-3.5*8/sqrt(42.0),-2.5*8/sqrt(42.0),-1.5*8/sqrt(42.0),-0.5*8/sqrt(42.0),
                     0.5*8/sqrt(42.0),1.5*8/sqrt(42.0),2.5*8/sqrt(42.0),3.5*8/sqrt(42.0)};
gr_complex QAM16[] = {gr_complex(-3*_mag_/2,-3*_mag_/2), gr_complex(-3*_mag_/2,-_mag_/2),
                      gr_complex(-3*_mag_/2,3*_mag_/2), gr_complex(-3*_mag_/2,_mag_/2),
                      gr_complex(-_mag_/2,-3*_mag_/2), gr_complex(-_mag_/2,-_mag_/2),
                      gr_complex(-_mag_/2,3*_mag_/2), gr_complex(-_mag_/2,_mag_/2),
                      gr_complex(3*_mag_/2,-3*_mag_/2), gr_complex(3*_mag_/2,-_mag_/2),
                      gr_complex(3*_mag_/2,3*_mag_/2), gr_complex(3*_mag_/2,_mag_/2),
                      gr_complex(_mag_/2,-3*_mag_/2), gr_complex(_mag_/2,-_mag_/2),
                      gr_complex(_mag_/2,3*_mag_/2), gr_complex(_mag_/2,_mag_/2)};

modulations::modulations(ModParam *mod_param):
    is_running(false),
    run_thread_created(false),
    unlock_thread_created(false)
{
    pthread_mutex_init(&is_running_mutex, NULL);

    //FIXME:
    // checking mod_param does not have any empty components

    fg_update(mod_param);
}

void modulations::print_errs(char err)
{
    cout << "\n\t* * *" << ERRORS[err] << "* * *" << endl;
}

// flowgraph control routines
bool modulations::run_fg()
{
    pthread_mutex_lock(&is_running_mutex);
    if (!is_running)
    {
        is_running = true;
        pthread_create(&run_hndlr, NULL, call_run, this);
        pthread_mutex_unlock(&is_running_mutex);
        run_thread_created = true;
        return true;
    }
    pthread_mutex_unlock(&is_running_mutex);
    return false;
}

bool modulations::lock_fg()
{

}

bool modulations::unlock_fg()
{

}

bool modulations::stop_fg()
{
    pthread_mutex_lock(&is_running_mutex);
    is_running = false;
    pthread_mutex_unlock(&is_running_mutex);

    cout << "The flowgraph is DESTROYED" << endl;
    if(run_thread_created)
    {
//        tb->lock();
//        tb->stop();
        pthread_cancel(run_hndlr);
    }
    if(unlock_thread_created)
        pthread_cancel(unlock_hndlr);

    tb->disconnect_all();

    return true;

}

void modulations::disconnect_all()
{

}

////////////////////////////// flowgraphs
void modulations::fg_update(ModParam *mod_param)
{
    tb = gr::make_top_block("top block");
    Mod_t mod_type = mod_param->Mod_type;
    if (mod_type == PSK || mod_type == PAM || mod_type == QAM)
    {
        char err = PSK_fg(mod_param);
        if (err!=TRUE)
        {
            print_errs(err);
            throw runtime_error("The flowgraph cannot be generated");
        }

    }
    else if (mod_type == DQPSK)
    {

    }
    // ... ifs to be continued
}

char modulations::PSK_fg(ModParam *mod_param)
{
    int nbits_per_symb = log2((double) mod_param->Mod_order);

    pack_bits = gr::blocks::pack_k_bits_bb::make(nbits_per_symb);

    vector<gr_complex> constpoints;
    if (mod_param->Mod_order == 2)
    {
        if (mod_param->Mod_type == PSK)
        {
            constpoints.assign(PSK2,PSK2+2);
        }
        else // PAM2
        {
            constpoints.assign(PAM2,PAM2+2);
        }
    }
    else if (mod_param->Mod_order == 4)
    {
        if (mod_param->Mod_type == PSK || mod_param->Mod_type == QAM)
        {
            constpoints.assign(PSK4,PSK4+4);
        }
        else //PAM
        {
            constpoints.assign(PAM4,PAM4+4);
        }

    }
    else if (mod_param->Mod_order == 8)
    {
        if (mod_param->Mod_type == PSK)
        {
            constpoints.assign(PSK8,PSK8+8);
        }
        else //PAM
        {
            constpoints.assign(PAM8,PAM8+8);
        }

    }
    else if (mod_param->Mod_order == 16 && mod_param->Mod_type == QAM)
    {
        constpoints.assign(QAM16,QAM16+16);
    }
    else
    {
        return MOD_ORDER_UNDEFINED;
    }

    mod_mapper = gr::digital::chunks_to_symbols_bc::make(constpoints, 1);

    vector<float> fltTaps;
    if (mod_param->LPulseShape == RRC)
    {
        fltTaps = gr::filter::firdes::root_raised_cosine(1, mod_param->SampRate,
                                                     mod_param->SampRate/mod_param->SPS,
                                                     mod_param->RollOff, 11 * mod_param->SPS );
    }
    else if (mod_param->LPulseShape == RC)
    {
//        fltTaps = filter::firdes::
    }
    else
    {
        return PULSE_SHAPING_UNDEFINED;
    }


    // GUIs
    flt = gr::filter::interp_fir_filter_ccf::make(mod_param->SPS, fltTaps);
    freq_snk = gr::qtgui::freq_sink_c::make(128, gr::filter::firdes::WIN_HAMMING, 0,
                                        mod_param->SampRate, "output spectrum", 1, &freq_wgd);
    freq_snk->set_size(700,400);
    freq_snk->enable_autoscale();
    freq_snk->enable_grid();
    freq_snk->set_fft_average(.1);
    time_snk = gr::qtgui::time_sink_c::make(1024, mod_param->SampRate, "time", 1, &time_wgd);
    time_snk->set_size(700,400);
    time_snk->enable_autoscale();
    const_snk = gr::qtgui::const_sink_c::make(128, "Output constellation", 1, &const_wgd);
    const_snk->set_size(700,400);
    const_snk->enable_autoscale(true);

    chr_to_flt = gr::blocks::char_to_float::make(1);

    // output sptr for GUI handler
    output_sptr = flt;
    in_sptr = pack_bits;

    // connections
    tb->connect(pack_bits, 0, mod_mapper, 0);
    tb->connect(mod_mapper, 0, flt, 0);
//    tb->connect(pack_bits, 0, chr_to_flt, 0);
    tb->connect(flt, 0, freq_snk, 0);
    tb->connect(flt, 0, time_snk, 0);
    tb->connect(mod_mapper, 0, const_snk, 0);
    return TRUE;
}

char modulations::DPSK_fg(ModParam *mod_param)
{

}

/////////////////////// threads ///////////////////////////////////////
void *modulations::run_thread(void *)
{
    cout << "The flowgraph is going to RUN" << endl;
    tb->run();
}
