#include "mainwindow.h"
#include <QApplication>
#include <modulations.h>
#include <QPlainTextEdit>
//#include <gnuradio/analog/random_uniform_source_b.h>

using namespace std;

//class handlEvent : public QObject
//{
//public:
//    handlEvent(){
//        cout << "the Event Handler is constructed" << endl;
//    }

//protected:
//    bool eventFilter(QObject *obj, QEvent *ev)
//    {
//        if (ev->type()==QEvent::Close)
//        {
//            // do nothing!
//            return true;
//        }

//        return false;
//    }
//};

int main(int argc, char *argv[])
{

//    modulations::ModParam mod_parameters;
//    mod_parameters.Mod_type = modulations::PSK;
//    mod_parameters.Mod_order = 4;
//    mod_parameters.SymbolOrder = modulations::Gray;
//    mod_parameters.LPulseShape = modulations::RRC;
//    mod_parameters.SPS = 5;
//    mod_parameters.RollOff = 0.35;
//    mod_parameters.SampRate = 100e3;

//    modulations mod_des(&mod_parameters);
//    gr::block_sptr mod_int = mod_des.get_in_sptr();
//    gr::block_sptr mod_out = mod_des.get_output_sptr();
//    gr::top_block_sptr tb = mod_des.get_top_block_sptr();

//    gr::analog::random_uniform_source_b::sptr rnd_in =
//            gr::analog::random_uniform_source_b::make(0,255, .1);
//    gr::qtgui::freq_sink_c::sptr freq_snk =
//            gr::qtgui::freq_sink_c::make(1024, gr::filter::firdes::WIN_HAMMING, 0, mod_parameters.SampRate,
//                                         "output spec");


    QApplication a(argc, argv);
    MainWindow w(NULL);
    w.show();

//    handlEvent HEv;

//    QMdiArea mdiarea_1;
//    mdiarea_1.setMinimumSize(200,200);
//    QPlainTextEdit pte;
//    Qt::WindowFlags flags;
//    flags = Qt::Window | Qt::WindowMinimizeButtonHint;
//    QMdiSubWindow *sub1 = mdiarea_1.addSubWindow(&pte, flags);
//    sub1->installEventFilter(&HEv);
//    sub1->setFocusPolicy(Qt::ClickFocus);
//    mdiarea_1.show();
    return a.exec();
}

