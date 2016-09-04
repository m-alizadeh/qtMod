#ifndef RADIO_H
#define RADIO_H

#include <gnuradio/uhd/usrp_sink.h>
#include <uhd/types/device_addr.hpp>
#include <uhd/stream.hpp>
#include <uhd/device.hpp>
#include <uhd/usrp/multi_usrp.hpp>

using namespace std;
//using namespace gr;
//using namespace uhd;

class Radio
{

public:
    typedef struct{
        double fc;
        double samp_rate;
        double gain;
        double master_clk_rate;
        char *ant;
        char *cpu_t;
        char *otw_t;
        char *sub_dev_spec;
    } RadioParam;

    typedef struct {
        int min_gain;
        int max_gain;
        uint min_freq;
        uint max_freq;
        int nchans;             // number of channels on a specific device
        vector<string> ants;    // list of all TX antennas on a specific device
        vector<string> type;    // list of all USRPs type
        vector<string> addr;    // list of all USRPs addresses
        int nDevs;              // number of devices found
    } DevsParam;

    // FIXME: two times the device is updated
    Radio();
    bool Radio_init(RadioParam *radio_param, gr::uhd::usrp_sink::sptr &u);

    // find device parameters
    void FindDevParams(int idx, DevsParam &devparam);
    DevsParam getdevsparam() { return d_devsparam;};

private:
    // uhd
    uhd::stream_args_t *ustream;
    gr::uhd::usrp_sink::sptr usrp;
    uhd::device_addr_t hint;
    uhd::device_addrs_t devs;

    DevsParam d_devsparam;
};

#endif // RADIO_H
