#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "modulations.h"
#include "radio.h"

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QComboBox>
#include <QFileDialog>
#include <QTextEdit>
#include <QMessageBox>
#include <QFrame>
#include <QRadioButton>
#include <QPixmap>
#include <QGroupBox>
#include <QLineEdit>
#include <gnuradio/blocks/file_source.h>
#include <gnuradio/analog/random_uniform_source_b.h>
#include <gnuradio/qtgui/freq_sink_c.h>
#include <gnuradio/filter/firdes.h>
#include <gnuradio/blocks/file_sink.h>
#include <QShortcut>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QScrollArea>
#include <QKeyEvent>
#include <QMouseEvent>
#include <cstdlib>
#include <QProcess>
#include <pthread.h>

class modulations;
class radio;

//using namespace gr;
namespace Ui {
class MainWindow;
}

/*!
 * \brief The MainWindow class
 *
 * \attention All "USRP" usages have been commented out to avoid of using USRP.
 *  If there is any USRP available, then activate them.
 */

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

    /// for quitting the MainWindow ESCAPE KEY pressing
    void keyPressEvent(QKeyEvent *ev);

    /// An event filter for handling minimizing or normal show of subwindows
    //FIXME: bring the subwindows on the top if they are not
    bool eventFilter(QObject *object, QEvent *ev);

    Ui::MainWindow *ui;
    modulations *mod_fg;
    Radio *USRP;
    modulations::ModParam *mod_params;
    Radio::RadioParam *usrp_params;
    Radio::DevsParam Devparam;
    char make_fg();

    gr::top_block_sptr top_block;
    gr::block_sptr mod_output;
    gr::uhd::usrp_sink::sptr usrp_in;
    gr::block_sptr mod_input;
    gr::blocks::file_source::sptr file_src;
    gr::analog::random_uniform_source_b::sptr rnd_src;
    gr::qtgui::freq_sink_c::sptr freq_snk;
//    gr::blocks::file_sink::sptr file_snk;

    gr::blocks::char_to_float::sptr chr_to_flt;

    ///////////// GUI Components ////////////////////

    // modulation box
    QGroupBox mod_frm;
    QLabel mod_type;
    QGridLayout mod_frm_grd;
    QComboBox mod_cmb;
    QLabel mod_order_lbl;
    QComboBox mod_order_cmb;
    QLabel sym_ord_lbl;
    QComboBox sym_ord_cmb;
    QLabel pulse_shap_lbl;
    QComboBox pulse_shap_cmb;
    QFrame pulse_frm;
    QGridLayout pulse_grd;
    QLabel rolloff_lbl;
    QLineEdit rolloff_led;
    QLabel sps_lbl;
    QLineEdit sps_txt;

    // input box
    QLabel input;
    QGroupBox input_frm;
    QGridLayout in_grd;
    QRadioButton rnd_radio_btm;
    QRadioButton file_radio_btm;
    QPixmap in_arrow;
    QLabel arrow_lbl_1;
    QLabel file_path_lbl;
    QLineEdit file_path_led;
    QPushButton file_brws_btm;
    QGridLayout file_in_grd;
    QFileDialog file_dlg;
    string FilePath;

    // Radio box
    QGroupBox radio_frm;
    QLabel dev_addr_ldl;
    QComboBox dev_addr_cmb;
    QLabel fc_lbl;
    QLineEdit fc_led;
    QComboBox fc_unit_cmb;
    QLabel samp_rate_lbl;
    QLineEdit samp_rate_led;
    QLabel gain_lbl;
    QLineEdit gain_led;
    QLabel ant_lbl;
    QComboBox ant_cmb;
    QLabel arrow_lbl_2;
    QGridLayout radio_frm_grd;
    QLabel master_clk_lbl;
    QLineEdit master_clk_led;
    QLabel chan_sel_lbl;
    QComboBox chan_sel_cmb;
    bool master_clk_available;

    // output subwindow
    QPushButton start_stop;
    QGridLayout Maingrd;
    QTabWidget tabs;
    QScrollArea scrol_output;

    // StatusBar
    QLabel warning_lbl;
    QLabel warning_msg;
    QLabel fg_status;

    // menubar
    QAction *exit;
    QAction *about_act;
    QMessageBox about_msg;
    QShortcut *shortcut;

    // mdi aread
    Qt::WindowFlags flags;  // removing close flag of the subwindow
    QMdiArea mdiArea;
    QMdiSubWindow *subwinInput;
    QMdiSubWindow *subwinMod;
    QMdiSubWindow *subwinRadio;
    QMdiSubWindow *subwinOutput;
    QLabel input_lbl;
    QLabel mod_lbl;
    QLabel radio_lbl;
    QLabel output_lbl;
    QGridLayout mdi_grd;
    QGridLayout center_grd;

    // stdout to qtextEdit
    QProcess qpros;
    QTextEdit qedt;
    pthread_t ph;
    void* call_run_process(void *);
    static void* run_process(void *arg) {return ((MainWindow *) arg)->call_run_process(NULL); }

    ////////////////////////////////////
    /// auxilary functions
    void CreatMenu();
    void CreatInput();
    void CreatMod();
    void CreatRadio();
    void connections();
    void CreatStatusBar();
    void SignalSlotConnection();

    void SetEnableParams(bool en);

    string int2string(int in);
    string double2string(double in);

private slots:
    void start_fg(void);
    void file_in(void);
    void open_file_dlg(void);

    // updating modulation parameters
    void mod_type_updt(void);
    void mod_order_updt(void);
    void mod_symorder_updt(void);
    void mod_pulse_updt(void);
    void mod_rolloff_updt(void);
    void mod_sps_updt(void);

    // updating radio parameters
    void dev_addr_updt(void);
    void fc_updt(void);
    void samp_rate_updt(void);
    void gain_updt(void);
    void ant_updt(void);
    void chan_sel_updt(void);
    void master_clk_updt(void);
    void dev_changed(void);

    // about slot
    void about_slt(void);

    // sub wins slots
    void SWinInMaximize(void);
    void SWinModMaximize(void);
    void SWinRadioMaximize(void);
    void SWinOutMaximize(void);

    void handleprocErr(void);
};

#endif // MAINWINDOW_H
