/* -*- c++ -*- */
/*
 * Copyright 2011 Alexandru Csete OZ9AEC.
 *
 * Gqrx is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * Gqrx is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Gqrx; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */
#ifndef BPSK1000WIN_H
#define BPSK1000WIN_H

#include <QMainWindow>
#include <QVarLengthArray>
#include <QProcess>


namespace Ui {
    class Bpsk1000Win;
}


/*! \brief BPSK1000 decoder window.
 *
 * This is the top level class for decoding BPSK1000 telemetry data from ARISSat-1.
 * It uses the reference demodulator by Phil Karn, KA9Q, see http://www.ka9q.net/
 *
 * The demodulator application is started using QProcess. Data is excahnged via stdin
 * and stdout, which are automatically available when starting external processes
 * using QProcess.
 *
 * Incoming samples from the SDR chain are provided periodically by the main application.
 * These samples 48ksps float format -1.0 ... +1.0 and need to be converted to 16 bit
 * signed integer, see http://wiki.oz9aec.net/index.php/Demod2
 *
 * The decoded data is shown in HEX format in the textview (one packet per line) and
 * optionally dumped to a text file.
 */
class Bpsk1000Win : public QMainWindow
{
    Q_OBJECT

public:
    explicit Bpsk1000Win(QWidget *parent = 0);
    ~Bpsk1000Win();
    void process_samples(float *buffer, int length);

protected:
    void closeEvent(QCloseEvent *ev);

signals:
    void windowClosed();  /*! Signal we emit when window is closed. */

private slots:
    void demodStateChanged(QProcess::ProcessState newState);
    void readDemodData();

    // button actions
    void on_actionClear_triggered();
    void on_actionSave_triggered();
    void on_actionInfo_triggered();

private:
    Ui::Bpsk1000Win *ui;  /*! Qt Designer form. */

    QProcess *demod;  /*! Demodulator process. */

    quint64 demodBytes;    /*! Bytes received from demod. */
    quint64 demodFramesT;  /*! TLM frames received from demod. */
    quint64 demodFramesB1; /*! E1B1 frames received from demod. */
    quint64 demodFramesB2; /*! E1B2 frames received from demod. */
    quint64 demodFramesB3; /*! E1B3 frames received from demod. */
    quint64 demodFramesB4; /*! E1B4 frames received from demod. */
};

#endif // BPSK1000WIN_H
