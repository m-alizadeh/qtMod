#ifndef MODULATIONS_H
#define MODULATIONS_H

// defining errors
#define MOD_T_NOT_DEFINED       0x00
#define TRUE                    0x01
#define MOD_ORDER_UNDEFINED     0x02
#define PULSE_SHAPING_UNDEFINED 0x03
#define MOD_PARAM_NULL          0x04


#include <gnuradio/top_block.h>
#include <cmath>
#include <QWidget>

#include <gnuradio/digital/chunks_to_symbols_bc.h>
#include <gnuradio/filter/firdes.h>
#include <gnuradio/filter/interp_fir_filter_ccf.h>  // for interpolating filter
#include <gnuradio/filter/fir_filter_ccf.h>         // for decimating filter
#include <gnuradio/digital/constellation_decoder_cb.h>
#include <gnuradio/digital/constellation.h>
#include <gnuradio/blocks/pack_k_bits_bb.h>
#include <gnuradio/blocks/char_to_float.h>
#include <gnuradio/qtgui/freq_sink_c.h>
#include <gnuradio/qtgui/time_sink_c.h>
#include <gnuradio/qtgui/time_sink_f.h>
#include <gnuradio/qtgui/const_sink_c.h>


using namespace std;
//using namespace gr;

/*!
 * \brief The modulations class
 *
 * Detailed description: ...
 * \todo The input bits must be unpack for all of the modulation types.
 *
 *
 *
 *
 *
*/

class modulations
{
public:

    ////////// defining parameters
    ///
    string ERRORS[5] ={"Modulation type is not defined",
                       "OK!",
                       "Modulation order is no defined",
                       "Pulse shaping is no defined",
                       "Modulation parameter is not defined"};

    // modulation types
    typedef enum {
        PSK = 0,
        PAM,
        QAM,
        DQPSK,
        OQPSK,
        DBPSK,
        APSK,
        FSK,
        CPFSK,
        CPM,
        FM
    }Mod_t;
    // modulation text
    string mod_txt[11] = {"PSK","PAM","QAM","DQPSK","OQPSK","DBPSK","APSK","FSK","CPFSK","CPM","FM"};

    // symbol ordering
    typedef enum{
        Binary,
        Gray
    } SymOrder;

    // linear pulse shaping, hence LPS (Root raised cosine or raised cosine)
    typedef enum{
        RC,
        RRC
    } LPS;


    typedef struct {
        Mod_t Mod_type;
        uint Mod_order;
        SymOrder SymbolOrder;
        LPS LPulseShape;
        uint SPS;   // interpolation factor
        float RollOff;
        uint SampRate;
    }ModParam;


    modulations(ModParam *mod_param);
    void print_errs(char err);

    ////////// flowgraph controls
    // updating PHY flowgraph blocks' connections
//    bool update_fg(LTE_PHY_DL_STRUCT phy_strc,
//                                 LTE_PHY_PDSCH_CONF_STRUCT pdsch_strc,
//                                 _gui_param gui_strc);
    bool run_fg();
    bool lock_fg();                                   // lock topblock = pause topblock
    bool unlock_fg();                                 // unlock topblock after a lock
//    bool restart_fg(LTE_PHY_DL_STRUCT phy_strc,
//                                  LTE_PHY_PDSCH_CONF_STRUCT pdsch_strc,
//                                  _gui_param gui_strc);             // stop+run topblock
    bool stop_fg();                                   // destroy topblock
    void fg_update(ModParam *mod_param);
    void disconnect_all();

    ////////// input/output of the fg
    gr::top_block_sptr get_top_block_sptr() { return tb; }
    gr::block_sptr get_output_sptr() { return output_sptr; }
    gr::block_sptr get_in_sptr() { return in_sptr; }
    QWidget* get_freq_widget() { return &freq_wgd; }
    QWidget* get_time_widget() { return &time_wgd; }
    QWidget* get_const_widget() { return &const_wgd; }

private:
    ////////// gnuradio blocks
    gr::top_block_sptr  tb;
    gr::block_sptr output_sptr;
    gr::block_sptr in_sptr;
    gr::blocks::pack_k_bits_bb::sptr pack_bits;
    gr::digital::chunks_to_symbols_bc::sptr mod_mapper;
    gr::filter::interp_fir_filter_ccf::sptr flt;

    // qt GUIs
    gr::qtgui::freq_sink_c::sptr freq_snk;
    gr::qtgui::time_sink_c::sptr time_snk;
    gr::qtgui::time_sink_f::sptr time_snk_f;
    gr::blocks::char_to_float::sptr chr_to_flt;
    gr::qtgui::const_sink_c::sptr const_snk;

    QWidget freq_wgd;
    QWidget time_wgd;
    QWidget const_wgd;

    ////////// necessary threads
    pthread_t       run_hndlr;      // Handler of running FG
    pthread_t       unlock_hndlr;   // Handler of unlocking FG
    void *run_thread (void*);
    void *unlock_thread(void*);
    static void *call_run(void *arg) {return ((modulations*) arg)->run_thread(NULL); }
    static void *call_unlock(void *arg) {return ((modulations*) arg)->run_thread(NULL); }

    ////////// necessary mutexes
    pthread_mutex_t is_running_mutex;
    bool is_running;
    bool run_thread_created;
    bool unlock_thread_created;

    ////////// modulation flowgraphs
    char PSK_fg(ModParam *mod_param);
    char DPSK_fg(ModParam *mod_param);

};

#endif // MODULATIONS_H
