#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    if(mod_param == NULL)
//    {
////        print_errs(MOD_PARAM_NULL);
//        throw runtime_error("");
//    }

    CreatMenu();
    CreatInput();
    CreatMod();
    CreatRadio();
    CreatStatusBar();
    SignalSlotConnection();

    /////////////// Making Main Grid ////////////////////

    start_stop.setText("Start");
    start_stop.setMaximumWidth(100);
    Maingrd.addWidget(&tabs, 1,1,1,2);
    Maingrd.addWidget(&start_stop, 2,2,1,1);

    scrol_output.setLayout(&Maingrd);
    tabs.setFixedSize(700,450);

    /////////////////// Mdi Area //////////////////
    flags = Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowTitleHint;

    mdiArea.setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea.setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea.setMinimumSize(1000,600);

    // sub win icons
    QIcon subWinIcons(":/new/icons/arrow.png");
    subwinInput = mdiArea.addSubWindow(&input_frm, flags);
    subwinInput->setMinimumSize(200,400);
    subwinInput->setWindowTitle("Input parameters");
    subwinInput->setWindowIcon(subWinIcons);
    subwinInput->showMinimized();

    subwinMod = mdiArea.addSubWindow(&mod_frm, flags);
    subwinMod->setWindowTitle("Modulation parameters");
    subwinMod->setWindowIcon(subWinIcons);
    subwinMod->showMinimized();

    subwinRadio = mdiArea.addSubWindow(&radio_frm, flags);
    subwinRadio->setWindowTitle("Radio parameters");
    subwinRadio->setWindowIcon(subWinIcons);
    subwinRadio->showMinimized();

    subwinOutput = mdiArea.addSubWindow(&scrol_output, flags);
    subwinOutput->setMinimumSize(200,200);
    subwinOutput->setWindowTitle("Output");
    subwinOutput->setWindowIcon(subWinIcons);
    subwinOutput->showMinimized();

    ////// making labels
    input_lbl.setPixmap(QPixmap(":/new/icons/input_icon_2.svg").scaledToHeight(100));
    input_lbl.setCursor(QCursor(Qt::OpenHandCursor));
    input_lbl.installEventFilter(this);
    input_lbl.setMaximumWidth(100);

    mod_lbl.setPixmap(QPixmap(":/new/icons/mod_icon.png").scaledToHeight(100));
    mod_lbl.setCursor(QCursor(Qt::OpenHandCursor));
    mod_lbl.installEventFilter(this);

    radio_lbl.setPixmap(QPixmap(":/new/icons/radio_icon.png").scaledToHeight(100));
    radio_lbl.setCursor(QCursor(Qt::OpenHandCursor));
    radio_lbl.installEventFilter(this);

    output_lbl.setPixmap(QPixmap(":/new/icons/constellation_icon_2.png").scaledToHeight(100));
    output_lbl.setCursor(QCursor(Qt::OpenHandCursor));
    output_lbl.installEventFilter(this);
    output_lbl.setFocusPolicy(Qt::ClickFocus);

    mdi_grd.addWidget(&input_lbl, 1,1,1,1,0);
    mdi_grd.addWidget(&mod_lbl, 2,1,1,1,0);
    mdi_grd.addWidget(&radio_lbl, 3,1,1,1,0);
    mdi_grd.addWidget(&output_lbl, 4,1,1,1,0);

    center_grd.addLayout(&mdi_grd, 1,1,4,1);
    center_grd.addWidget(&mdiArea, 1,2,4,4);
    centralWidget()->setLayout(&center_grd);

}

MainWindow::~MainWindow()
{
    delete ui;
}

///////////////////////////// creating GUI
///
void MainWindow::CreatMenu()
{
    // file menu
    QMenu *file_mnu     = menuBar()->addMenu("File");
    exit = file_mnu->addAction(QString("Exit"));
    shortcut = new QShortcut(QKeySequence::Quit, this);
    exit->setShortcut(shortcut->key());

    // about menu
    QMenu *About_mnu    = menuBar()->addMenu("About");
    about_act = About_mnu->addAction(QString("About"));
}
void MainWindow::CreatInput()
{
    rnd_radio_btm.setChecked(true);
    rnd_radio_btm.setText("Random input");
    rnd_radio_btm.setMinimumHeight(20);
    file_radio_btm.setText("File input");
    file_radio_btm.setMinimumHeight(20);
    file_path_lbl.setText("File path: ");
    file_path_lbl.setMargin(20);
    file_path_led.setReadOnly(true);
    file_brws_btm.setText("Brows");

    in_grd.addWidget(&rnd_radio_btm,1,1,1,1,0);
    in_grd.addWidget(&file_radio_btm, 2,1,1,1,0);
    in_grd.addWidget(&file_path_lbl,3,1,1,1,0);
    in_grd.addWidget(&file_path_led,4,1,1,1,0);
    in_grd.addWidget(&file_brws_btm,5,1,1,1,0);
    input_frm.setLayout(&in_grd);
    input_frm.setTitle("Input settings");
    input_frm.setStyleSheet("QGroupBox { border: 1px solid gray; border-radius: 9px; margin-top: 1em;}");

    // make disappearing these widgets @ startup
    file_path_lbl.close();
    file_brws_btm.close();
    file_path_led.close();

}
void MainWindow::CreatMod()
{
    // Setting defaul modulation parameters
    mod_params = new modulations::ModParam;
    mod_params->Mod_type = modulations::PSK;
    mod_params->Mod_order = 2;
    mod_params->SymbolOrder = modulations::Gray;
    mod_params->LPulseShape = modulations::RRC;
    mod_params->RollOff = 0.35;
    mod_params->SPS = 4;
    mod_params->SampRate = 1e6;
    mod_fg = new modulations (mod_params);

    // modulation box
    mod_frm.setTitle("Modulation settings");
    mod_frm.setStyleSheet("QGroupBox { border: 1px solid gray; border-radius: 9px; margin-bottom: 1em;}");

    mod_type.setText("Modulation type: ");
    mod_type.setMargin(20);
    mod_type.show();

    mod_cmb.addItem("PSK");
    mod_cmb.addItem("PAM");
    mod_cmb.addItem("QAM");
    mod_cmb.addItem("DQPSK");
    mod_cmb.addItem("OQPSK");
    mod_cmb.addItem("DBPSK");
    mod_cmb.addItem("APSK");
    mod_cmb.addItem("FSK");
    mod_cmb.addItem("GFSK");
    mod_cmb.addItem("CPFSK");
    mod_cmb.addItem("CPM");
    mod_cmb.addItem("MSK");
    mod_cmb.addItem("GMSK");
    mod_cmb.addItem("FM");
    mod_cmb.addItem("NBFM");
    mod_cmb.addItem("WBFM");
    mod_cmb.addItem("AM");
    mod_cmb.setCurrentIndex(mod_params->Mod_type);

    mod_order_lbl.setText("Modulation order: ");
    mod_order_lbl.setMargin(20);
    // FIXME: this is just for PSK modulations only and
    // it will be added other modulations
    if (mod_params->Mod_type == modulations::PSK)
    {
        mod_order_cmb.addItems(QStringList{"2","4","8"});
        mod_order_cmb.setCurrentIndex(log2(mod_params->Mod_order)-1);
    }
    else
    {
        throw runtime_error("Modulation type is not supported yet");
    }

    sym_ord_lbl.setText("Symbol order: ");
    sym_ord_lbl.setMargin(20);
    sym_ord_cmb.addItems(QStringList {"Binary","Gray"});
    sym_ord_cmb.setCurrentIndex(mod_params->SymbolOrder);

    pulse_frm.setFrameStyle(QFrame::StyledPanel);
    pulse_shap_lbl.setText("Pulse Shaping: ");
    pulse_shap_lbl.setMargin(10);
    pulse_shap_cmb.addItems(QStringList {"RC", "RRC"});
    pulse_shap_cmb.setCurrentIndex(mod_params->LPulseShape);
    rolloff_lbl.setText("Rolloff: ");
    rolloff_lbl.setMargin(10);
//    rolloff_led.setValidator(new QDoubleValidator);
    rolloff_led.setText(to_string(mod_params->RollOff).c_str());
    pulse_grd.addWidget(&pulse_shap_lbl,1,1,1,1,0);
    pulse_grd.addWidget(&pulse_shap_cmb,1,2,1,1,0);
    pulse_grd.addWidget(&rolloff_lbl,2,1,1,1,0);
    pulse_grd.addWidget(&rolloff_led,2,2,1,1,0);
    pulse_frm.setLayout(&pulse_grd);

    sps_lbl.setText("Sample per symbol: ");
    sps_lbl.setMargin(20);
    sps_txt.setValidator(new QIntValidator(1,100) );
    sps_txt.setText(to_string(mod_params->SPS).c_str());

    mod_frm_grd.addWidget(&mod_type, 1,1,1,1,0);
    mod_frm_grd.addWidget(&mod_cmb, 1,2,1,1,0);
    mod_frm_grd.addWidget(&mod_order_lbl, 2,1,1,1,0);
    mod_frm_grd.addWidget(&mod_order_cmb, 2,2,1,1,0);
    mod_frm_grd.addWidget(&sym_ord_lbl,3,1,1,1,0);
    mod_frm_grd.addWidget(&sym_ord_cmb,3,2,1,1,0);
    mod_frm_grd.addWidget(&pulse_frm,4,1,2,2,0);
    mod_frm_grd.addWidget(&sps_lbl, 6,1,1,1,0);
    mod_frm_grd.addWidget(&sps_txt,6,2,1,1,0);
    mod_frm.setLayout(&mod_frm_grd);

    in_arrow.load("/home/mostafa/Dropbox/Kasri_2/arrow.png");
    arrow_lbl_1.setPixmap(in_arrow);
}
void MainWindow::CreatRadio()
{
    // radio default parameters
//    USRP = new Radio();
    usrp_params = new Radio::RadioParam;
//    Devparam = USRP->getdevsparam();
    usrp_params->cpu_t = "fc32";
    usrp_params->otw_t = "sc16";
    usrp_params->fc = 937.4e6;
    usrp_params->samp_rate = 1e6;
    usrp_params->gain = 15;
    usrp_params->ant = "TX/RX";
    usrp_params->sub_dev_spec = "A:A";  // by default the first channel
    // FIXME: we know only x series and B series and N series USRPs
    // Ifdef USRP:
//    if (!Devparam.type[0].compare("N210") ||
//            !Devparam.type[0].compare("N200"))
//    {
//        master_clk_available = false;
        usrp_params->master_clk_rate = 100e6;
//    }
//    else
//    {
//        master_clk_available = true;
//        usrp_params->master_clk_rate = 6e6;
//    }

    //// Radio box (by default the first found device)
    radio_frm.setTitle("Radio settings");
    radio_frm.setStyleSheet("QGroupBox { border: 1px solid gray; border-radius: 9px; margin-top: 1em;}");
    dev_addr_ldl.setText("Device address: ");
    dev_addr_ldl.setMargin(20);
    // Ifdef USRP:
//    for (int a=0; a<Devparam.nDevs; a++)
//    {
//        string temp = Devparam.type[a]+" , "+Devparam.addr[a];
//        dev_addr_cmb.addItem(temp.c_str());
//    }
    dev_addr_cmb.setMinimumWidth(70);
    fc_lbl.setText(QString("Carrier frequency:\n")
                   +QString("(")
                   +QString(int2string(Devparam.min_freq/1e6).c_str())
                   +QString("MHz")
                   +QString("-")
                   +QString(int2string(Devparam.max_freq/1e6).c_str())
                   +QString("MHz")
                   +QString(")"));
    fc_lbl.setMargin(20);

//    fc_led.setValidator(new QDoubleValidator);
    fc_led.setText(double2string((usrp_params->fc)/1e6).c_str());
    fc_unit_cmb.addItems(QStringList({"Hz","KHz","MHz","GHz"}));
    fc_unit_cmb.setCurrentIndex(2);
    samp_rate_lbl.setText("Sample rate: ");
    samp_rate_lbl.setMargin(20);
    samp_rate_led.setText(double2string(usrp_params->samp_rate).c_str());
    gain_lbl.setText(QString("Gain:\n")
                     +QString("(")
                     +QString(int2string(Devparam.min_gain).c_str())
                     +QString("-")
                     +QString(int2string(Devparam.max_gain).c_str())
                     +QString(")"));
    gain_lbl.setMargin(20);
    gain_led.setText(double2string(usrp_params->gain).c_str());
    ant_lbl.setText("Transmit antennas: ");
    ant_lbl.setMargin(20);
    for (int a=0; a<Devparam.ants.size(); a++)
    {
        ant_cmb.addItem(Devparam.ants[a].c_str());
    }
    master_clk_lbl.setText("master clock rate:");
    master_clk_lbl.setMargin(20);
    master_clk_led.setText(double2string(usrp_params->master_clk_rate).c_str());

    // if master clock rate is not available for the default USRP
    master_clk_led.setEnabled(master_clk_available);
    chan_sel_lbl.setText("channel:");
    chan_sel_lbl.setMargin(20);
    for (int a=0; a<Devparam.nchans; a++)
        chan_sel_cmb.addItem(int2string(a+1).c_str());

    radio_frm_grd.addWidget(&dev_addr_ldl, 1,1,1,2,0);
    radio_frm_grd.addWidget(&dev_addr_cmb, 1,2,1,2,0);
    radio_frm_grd.addWidget(&chan_sel_lbl, 2,1,1,1,0);
    radio_frm_grd.addWidget(&chan_sel_cmb, 2,2,1,2,0);
    radio_frm_grd.addWidget(&fc_lbl, 3,1,1,1,0);
    radio_frm_grd.addWidget(&fc_led, 3,2,1,1,0);
    radio_frm_grd.addWidget(&fc_unit_cmb,3,3,1,1,0);
    radio_frm_grd.addWidget(&samp_rate_lbl, 4,1,1,2,0);
    radio_frm_grd.addWidget(&samp_rate_led, 4,2,1,2,0);
    radio_frm_grd.addWidget(&master_clk_lbl, 5,1,1,2,0);
    radio_frm_grd.addWidget(&master_clk_led, 5,2,1,2,0);
    radio_frm_grd.addWidget(&gain_lbl, 6,1,1,2,0);
    radio_frm_grd.addWidget(&gain_led, 6,2,1,2,0);
    radio_frm_grd.addWidget(&ant_lbl, 7,1,1,2,0);
    radio_frm_grd.addWidget(&ant_cmb, 7,2,1,2,0);
    radio_frm.setLayout(&radio_frm_grd);

    arrow_lbl_2.setPixmap(in_arrow);
}
void MainWindow::CreatStatusBar()
{
    warning_lbl.setText("Warnings: ");
    warning_msg.setStyleSheet("QLabel { color : red; }");
    statusBar()->addWidget(&warning_lbl);
    fg_status.setStyleSheet("QLabel {color : blue;}");
    statusBar()->addWidget(&warning_msg,4);
    statusBar()->addWidget(&fg_status,2);

}
void MainWindow::SignalSlotConnection()
{
    connect(&start_stop, SIGNAL(clicked()), this, SLOT(start_fg()) );
    connect(&file_radio_btm, SIGNAL(toggled(bool)), this, SLOT(file_in()));
    connect(&file_brws_btm, SIGNAL(clicked()), this, SLOT(open_file_dlg()));

    // updating modulation parameters:
    connect(&mod_cmb, SIGNAL(currentIndexChanged(int)), this, SLOT(mod_type_updt()));
    connect(&mod_order_cmb, SIGNAL(currentIndexChanged(int)), this, SLOT(mod_order_updt()));
    connect(&sym_ord_cmb, SIGNAL(currentIndexChanged(int)), this, SLOT(mod_symorder_updt()));
    connect(&pulse_shap_cmb, SIGNAL(currentIndexChanged(int)), this, SLOT(mod_pulse_updt()));
    connect(&rolloff_led, SIGNAL(textChanged(QString)), this, SLOT(mod_rolloff_updt()));
    connect(&sps_txt, SIGNAL(textChanged(QString)), this, SLOT(mod_sps_updt()));

    // updating radio parameters:
    connect(&dev_addr_cmb, SIGNAL(currentIndexChanged(int)), this, SLOT(dev_addr_updt()));
    connect(&fc_led, SIGNAL(textChanged(QString)), this, SLOT(fc_updt()));
    connect(&fc_unit_cmb, SIGNAL(currentIndexChanged(int)), this, SLOT(fc_updt()));
    connect(&samp_rate_led, SIGNAL(textChanged(QString)), this, SLOT(samp_rate_updt()));
    connect(&gain_led, SIGNAL(textChanged(QString)), this, SLOT(samp_rate_updt()));
    connect(&ant_cmb, SIGNAL(currentIndexChanged(int)), this, SLOT(ant_updt()));
    connect(&master_clk_led, SIGNAL(textChanged(QString)), this, SLOT(master_clk_updt()));
    connect(&chan_sel_cmb, SIGNAL(currentIndexChanged(int)), this, SLOT(chan_sel_updt()));
    connect(&dev_addr_cmb, SIGNAL(currentIndexChanged(int)), this, SLOT(dev_changed()));

    // menu
    connect(exit, SIGNAL(triggered()), this, SLOT(close()));
    connect(shortcut, SIGNAL(activated()), this, SLOT(close()));
    connect(about_act, SIGNAL(triggered()), this, SLOT(about_slt()));

    // mdi
    connect(&qpros, SIGNAL(error(QProcess::ProcessError)), this, SLOT(handleprocErr()));
}

char MainWindow::make_fg()
{
    mod_output  = mod_fg->get_output_sptr();
    mod_input      = mod_fg->get_in_sptr();
    top_block = mod_fg->get_top_block_sptr();

    // updating tabs
    tabs.addTab(mod_fg->get_freq_widget(),"Spectrum");
    tabs.addTab(mod_fg->get_time_widget(), "Time");
    tabs.addTab(mod_fg->get_const_widget(), "Constellaiton");

//    if (!USRP->Radio_init(usrp_params, usrp_in))
//    {
//        warning_msg.setText("master clock rate is not set correctly");
//        return 0;
//    }

    rnd_src = gr::analog::random_uniform_source_b::make(0,2,123);

//    chr_to_flt = gr::blocks::char_to_float::make(1);

//    file_snk = gr::blocks::file_sink::make(sizeof(gr_complex),
//                                       "out_tst", false);
    if (file_radio_btm.isChecked())
    {
        if(!file_path_led.text().isEmpty())
        {
            warning_msg.clear();
            file_src = gr::blocks::file_source::make(sizeof(char),
                                                 FilePath.c_str(), false);
            top_block->connect(file_src, 0, mod_input, 0);
        }
        else
        {
            warning_msg.setText("File input is not specified!");
            return 0;
        }
    }
    else
    {
        top_block->connect(rnd_src, 0, mod_input, 0);
    }

    // connections ...
//    top_block->connect(mod_output, 0, usrp_in, 0);
    return true;
}

void MainWindow::SetEnableParams(bool en)
{
    rnd_radio_btm.setEnabled(en);
    file_radio_btm.setEnabled(en);
    mod_cmb.setEnabled(en);
    mod_order_cmb.setEnabled(en);
    sym_ord_cmb.setEnabled(en);
    pulse_shap_cmb.setEnabled(en);
    rolloff_led.setEnabled(en);
    sps_txt.setEnabled(en);
    samp_rate_led.setEnabled(en);
    dev_addr_cmb.setEnabled(en);
    fc_led.setEnabled(en);
    fc_unit_cmb.setEnabled(en);
    samp_rate_led.setEnabled(en);
    gain_led.setEnabled(en);
    ant_cmb.setEnabled(en);
    file_path_led.setEnabled(en);
    file_brws_btm.setEnabled(en);
    master_clk_led.setEnabled(en);
    chan_sel_cmb.setEnabled(en);
}

///////////////////////////////// Slots ///////////////////////////////////
void MainWindow::start_fg()
{
    if (start_stop.text().compare("Start")==0)
    {
        start_stop.setText("Stop");
        mod_fg->fg_update(mod_params);

        if (!mod_cmb.currentText().compare("PSK"))
        {
            cout << "my external program is going to run ... " << endl;
            pthread_create(&ph, NULL, run_process, this);
        }
        if(make_fg())
        {
            cout << "I'm here .. " << endl;
            SetEnableParams(false);
            string txt;
            txt = "Transmitting "+to_string(mod_params->Mod_order)+
                    mod_fg->mod_txt[mod_params->Mod_type]+" on USRP ...";
            fg_status.setText(txt.c_str());
            mod_fg->run_fg();
        }
        else
        {
            start_stop.setText("Start");
        }
    }
    else    // start_stop.text() == "Stop"
    {
        start_stop.setText("Start");
        SetEnableParams(true);
        mod_fg->stop_fg();
        fg_status.clear();
        mod_fg->fg_update(mod_params);
        make_fg();
    }
}

void MainWindow::file_in()
{
    if (file_radio_btm.isChecked())
    {
        file_path_lbl.show();
        file_path_led.show();
        file_brws_btm.show();
    }
    else
    {
        file_brws_btm.close();
        file_path_lbl.close();
        file_path_led.close();
    }
}

void MainWindow::open_file_dlg()
{
    if (file_dlg.exec())
    {
        QStringList file_selected = file_dlg.selectedFiles();
        FilePath = file_selected.at(0).toStdString();
        file_path_led.setText(FilePath.c_str());
    }
}

///////////////////////////////// updating modulation parameters ////////////
void MainWindow::mod_type_updt(void )
{
    mod_params->Mod_type = modulations::Mod_t(mod_cmb.currentIndex());
    //    cout << "mod selected:  " << mod_fg->mod_txt[mod_params->Mod_type] << endl;
    // removing all modulation orders
//    cout << "number of items in modulation combobox " << mod_order_cmb.count() << endl;
    int ncombs = mod_order_cmb.count();
    for (int k=0; k<ncombs; k++)
    {
        mod_order_cmb.removeItem(0);
    }

    if (mod_params->Mod_type == modulations::QAM)
    {
        mod_order_cmb.addItem("4");
        mod_order_cmb.addItem("16");
    }
    else if (mod_params->Mod_type == modulations::PSK
             || mod_params->Mod_type == modulations::PAM)
    {
        mod_order_cmb.addItem("2");
        mod_order_cmb.addItem("4");
        mod_order_cmb.addItem("8");
    }
}
void MainWindow::mod_order_updt()
{
    int selectedmodOrder = mod_order_cmb.itemText(mod_order_cmb.currentIndex()).toInt();
    mod_params->Mod_order = selectedmodOrder;
//    mod_params->Mod_order = pow(2,(selectedmodOrder));
}
void MainWindow::mod_symorder_updt()
{
    mod_params->SymbolOrder = modulations::SymOrder(sym_ord_cmb.currentIndex());
}
void MainWindow::mod_pulse_updt()
{
    mod_params->LPulseShape = modulations::LPS(pulse_shap_cmb.currentIndex());
}
void MainWindow::mod_rolloff_updt()
{
    mod_params->RollOff = rolloff_led.text().toDouble();
//    cout << "new rollof =  " << mod_params->RollOff << endl;
}
void MainWindow::mod_sps_updt()
{
    mod_params->SPS = sps_txt.text().toDouble();
}

///////////////////// updating radio parameters ///////////////
void MainWindow::dev_addr_updt()
{
//    usrp_params->dev_addr = (char*) dev_addr_led.text().toStdString().c_str();
}
void MainWindow::fc_updt()
{
    usrp_params->fc = fc_led.text().toDouble() * pow(1e3,fc_unit_cmb.currentIndex());
}
void MainWindow::samp_rate_updt()
{
    usrp_params->samp_rate = samp_rate_led.text().toDouble();
    mod_params->SampRate = usrp_params->samp_rate;
}
void MainWindow::gain_updt()
{
    usrp_params->gain = gain_led.text().toDouble();
}
void MainWindow::ant_updt()
{
    usrp_params->ant =(char *) Devparam.ants[ant_cmb.currentIndex()].c_str();
}
void MainWindow::chan_sel_updt()
{
    if (chan_sel_cmb.currentIndex()==0)
        usrp_params->sub_dev_spec = "A:A";
    else
        usrp_params->sub_dev_spec = "A:B";
}
void MainWindow::master_clk_updt()
{
    usrp_params->master_clk_rate = master_clk_led.text().toDouble();
}
void MainWindow::dev_changed()
{
    USRP->FindDevParams(dev_addr_cmb.currentIndex(), Devparam);

    // updating gain and frequency ranges, antennas
    gain_lbl.setText(QString("Gain:\n")
                     +QString("(")
                     +QString(int2string(Devparam.min_gain).c_str())
                     +QString("-")
                     +QString(int2string(Devparam.max_gain).c_str())
                     +QString(")"));

    fc_lbl.setText(QString("Carrier frequency:\n")
                   +QString("(")
                   +QString(int2string(Devparam.min_freq/1e6).c_str())
                   +QString("MHz")
                   +QString("-")
                   +QString(int2string(Devparam.max_freq/1e6).c_str())
                   +QString("MHz")
                   +QString(")"));

    chan_sel_cmb.clear();
    for (int a=0; a<Devparam.nchans; a++)
        chan_sel_cmb.addItem(QString(a));

    ant_cmb.clear();
    for (int a=0; a<Devparam.ants.size(); a++)
        ant_cmb.addItem(Devparam.ants[a].c_str());

}

/////////////// menu slots ////////////////////////////
void MainWindow::about_slt()
{
    about_msg.setText(QString("This GUI is developed under supervision of \"Hesam Aliakbar\" ")
                      +QString("as a part of military services.\n\nCopyright")+QString((wchar_t)0xA9)
                      +QString(" 2016 by Mostafa Alizadeh\n")
                      +QString("All rights reserved. For any redistribution the permission of the \"Nasr\" is required. ")
                      +QString("For any bugs, please Email:\n\n")
                      +QString("m.alizadehee@gmail.com"));
    about_msg.show();
}

////////////// Sub wins Slots ////////////
///
void MainWindow::SWinInMaximize()
{
    subwinInput->showMaximized();
}
void MainWindow::SWinModMaximize()
{
    subwinMod->showMaximized();
}
void MainWindow::SWinRadioMaximize()
{
    subwinRadio->showMaximized();
}
void MainWindow::SWinOutMaximize()
{
    subwinOutput->showMaximized();
}

/////////////// Auxilary functions ////////////////////
string MainWindow::int2string(int in)
{
    stringstream a;
    a << in;

    return a.str();
}

string MainWindow::double2string(double in)
{
    stringstream a;
    a << in;

    return a.str();
}
/////////////// MainWindow events /////////////////////
void MainWindow::keyPressEvent(QKeyEvent *ev)
{
    if (ev->key() == Qt::Key_Escape)
    {
        this->close();
    }
}

bool MainWindow::eventFilter(QObject *object, QEvent *ev)
{
    if (ev->type()==QEvent::MouseButtonRelease)
    {
        QLabel *lbl = qobject_cast<QLabel *> (object);
        if (lbl == &input_lbl)
        {
            if (subwinInput->isMinimized())
                subwinInput->showNormal();
            else
                subwinInput->showMinimized();
//            else // is toplevel and not minimized
            return true;
        }
        else if(lbl == &mod_lbl)
        {
            if (subwinMod->isMinimized())
                subwinMod->showNormal();
            else
                subwinMod->showMinimized();
            return true;
        }
        else if (lbl == &radio_lbl)
        {
            if (subwinRadio->isMinimized())
                subwinRadio->showNormal();
            else
                subwinRadio->showMinimized();
            return true;
        }
        else if (lbl == &output_lbl)
        {
            if (subwinOutput->isMinimized())
            {
                subwinOutput->showNormal();
                subwinOutput->setFixedSize(750,550);
            }
            else
                subwinOutput->showMinimized();
            return true;
        }
    }

    return QObject::eventFilter(object, ev);
}

void* MainWindow::call_run_process(void *)
{
    qpros.start("/home/mostafa/Dropbox/Kasri_2/qt_modulations/uhd_tx_dpsk.py");
}

void MainWindow::handleprocErr()
{
    cout << "process error" << endl;
}
