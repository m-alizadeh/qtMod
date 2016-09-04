#include "radio.h"

Radio::Radio()
{
    // finding USRP devices and their parameters
    devs = uhd::device::find(hint);

    d_devsparam.nDevs = devs.size();
    // getting all devices' type and addresses
    for (int a=0; a<d_devsparam.nDevs; a++)
    {
        // FIXME: the product may not be the same as the device type
        // due to different image file on the device
        d_devsparam.type.push_back(devs[a]["product"]);
        if (!d_devsparam.type[a].compare("B210") ||
                !d_devsparam.type[a].compare("B200"))
            d_devsparam.addr.push_back(devs[a]["serial"]);
        else
        {
            d_devsparam.addr.push_back(devs[a]["addr"]);
        }
    }

    // getting device 0 parameters by default
    FindDevParams(0, d_devsparam);
}

bool Radio::Radio_init(RadioParam *radio_param, gr::uhd::usrp_sink::sptr &u)
{

    ustream = new uhd::stream_args_t(radio_param->cpu_t, radio_param->otw_t);
    usrp = gr::uhd::usrp_sink::make(hint, *ustream);
    usrp->set_subdev_spec(radio_param->sub_dev_spec);   // setting the channel for transmission
    usrp->set_center_freq(radio_param->fc);
    usrp->set_samp_rate(radio_param->samp_rate);
    usrp->set_antenna(radio_param->ant);
    usrp->set_gain(radio_param->gain);

    // setting master clock rate
    if (int(radio_param->master_clk_rate/radio_param->samp_rate) % 2 == 0)
    {
        usrp->set_clock_rate(radio_param->master_clk_rate);
    }
    else
    {
        return false;
//        double dec = floor(5e6/radio_param->samp_rate)+1;
//        // for skipping odd decimation
//        if ((int)dec%2==0)
//            usrp->set_clock_rate(radio_param->samp_rate*dec);
//        else
//            usrp->set_clock_rate(radio_param->samp_rate*(dec+1));
    }

    u = usrp;
    return true;
}

void Radio::FindDevParams(int idx, Radio::DevsParam &devparam)
{
    uhd::usrp::multi_usrp::sptr getDev = uhd::usrp::multi_usrp::make(devs[idx]);
    // FIXME: all for channel 0
    devparam.min_gain = getDev->get_tx_gain_range().start();
    devparam.max_gain = getDev->get_tx_gain_range().stop();
    devparam.min_freq = getDev->get_tx_freq_range().start();
    devparam.max_freq = getDev->get_tx_freq_range().stop();
    devparam.nchans = getDev->get_tx_num_channels();
    devparam.ants = getDev->get_tx_antennas();

//    cout << "\t\t\tmax freq:   " << devparam.max_freq << endl;
}
