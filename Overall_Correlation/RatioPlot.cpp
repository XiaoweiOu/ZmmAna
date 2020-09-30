// Displaying two histograms and their ratio or chi-square or just display one
// single histogram. Author: C.Wang (USTC) Time: 07.31.17
void RatioPlot()
{
    // Define two histograms. Note the X and Y title are defined
    // at booking time using the convention "Hist_title ; X_title ; Y_title"
    // Common Option
    bool DoSave = true;
    bool CReadin = false;
    char savefilename[100] = "NiiDataMC.jpg";
    bool Compare = true;
    bool DoRatio = false;
    bool DoChi2 = false;
    bool DoPull = false;
    bool DoDelta = false;
    bool SetXRange = false;
    bool AddHeader = true;
    bool DoRebin = false;

    // if SetXRange is true set these parameters
    double minX = 74;
    double maxX = 110;

    // if DoRebin is true set these parameters
    int RebinNumber1 = 1;
    int RebinNumber2 = 1;

    char Headername[100] = "DZero Internal";

    // If Compare is false use filename1 and plotname1 only!!!
    char filename1[100] =
        "smallplots.root";
    char filename2[100] = "smallplots.root";

    char plotname1[100] = "Data_LeptonEta";
    char plotname2[100] = "MC_LeptonEta";

    char Xtitle[100] = "|#eta^{l}|";
    char Ytitle[100] = "Number of N_{ii} Events";

    // If Compare is true, set the option below.
    bool DoNorm = false;

    char legendname1[100] = "Data";
    char legendname2[100] = "MC";

    // If Compare is false, set the option below.
    bool gridx = true;
    bool gridy = true;

    // If the Yaxis lable is too large and it covered the Yaxis title, use "move"
    // to move the title further. If you want to make ratio range larger, use
    // "ratiorangeadd" If not necessary, set these zero!!!
    double move = 0;
    double ratiorangeadd = -0.2;

    // Main code begins
    if (Compare)
    {
        TH1D *h1;
        TH1D *h2;

        if (CReadin)
        {
            std::string name1 = filename1;
            std::string temp1 = string(".x ") + name1;
            gROOT->ProcessLine(temp1.c_str());
            h1 = (TH1D *)gROOT->FindObject(plotname1);

            std::string name2 = filename2;
            std::string temp2 = string(".x ") + name2;
            gROOT->ProcessLine(temp2.c_str());
            h2 = (TH1D *)gROOT->FindObject(plotname2);
        }
        else
        {
            TFile *file1 = new TFile(filename1);
            TFile *file2 = new TFile(filename2);

            h1 = (TH1D *)file1->Get(plotname1);
            h2 = (TH1D *)file2->Get(plotname2);
        }

        if (DoRebin)
        {
            h1->Rebin(RebinNumber1);
            h2->Rebin(RebinNumber2);
        }

        if (SetXRange)
        {
            h1->GetXaxis()->SetRangeUser(minX, maxX);
            h2->GetXaxis()->SetRangeUser(minX, maxX);
        }
        else
        {
            minX = h1->GetXaxis()->GetBinLowEdge(1);
            maxX = h1->GetXaxis()->GetBinUpEdge(h1->GetXaxis()->GetNbins());
        }

        double inte1, inte2;
        inte1 = h1->Integral();
        inte2 = h2->Integral();

        if (DoNorm)
        {
            cout << "Normalize plot2 to plot1" << endl;
            cout << "before norm:   " << endl;
            cout << "integral of plot1  " << inte1 << endl;
            cout << "integral of plot2  " << inte2 << endl;
            cout << "norm factor of plot2  " << inte1 / inte2 << endl;

            h2->Scale(inte1 / inte2);
        }

        double minY, maxY, left;
        if (h1->GetMinimum() > h2->GetMinimum())
            minY = h2->GetMinimum();
        else
            minY = h1->GetMinimum();

        if (h1->GetMaximum() > h2->GetMaximum())
            maxY = h1->GetMaximum();
        else
            maxY = h2->GetMaximum();

        left = (maxY - minY) * 0.025;

        // if(minY-left<0&&minY>=0)
        // h1->GetYaxis()->SetRangeUser(0.01,maxY+left);
        // else
        h1->GetYaxis()->SetRangeUser(minY - left, maxY + 4 * left);

        // Define the Canvas
        TCanvas *c;
        if (DoRatio || DoChi2 || DoDelta)
            c = new TCanvas("c", "canvas", 1000, 1000);
        else
            c = new TCanvas("c", "canvas", 1000, 700);

        // Upper plot will be in pad1
        TPad *pad1;
        if (DoRatio || DoChi2 || DoDelta)
        {
            pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
            pad1->SetBottomMargin(0); // Upper and lower plot are joined
        }
        else
            pad1 = new TPad("pad1", "pad1", 0, 0, 1, 1.0);
        pad1->SetTopMargin(0.07);
        pad1->SetLeftMargin(0.15);
        pad1->SetRightMargin(0.05);
        pad1->SetGridx(); // Vertical grid
        pad1->SetGridy();
        pad1->Draw();    // Draw the upper pad: pad1
        pad1->cd();      // pad1 becomes the current pad
        h1->SetStats(0); // No statistics on upper plot
        h1->SetFillStyle(0);
        h2->SetFillStyle(0);
        h1->Draw("E0");      // Draw h1
        h2->Draw("E0 same"); // Draw h2 on top of h1

        // Do not draw the Y axis label on the upper plot and redraw a small
        // axis instead, in order to avoid the first label (0) to be clipped.
        h1->GetYaxis()->SetLabelSize(0.05);

        h1->GetYaxis()->SetTitle(Ytitle);
        h1->SetTitle("");

        TLegend *legend = new TLegend(0.18, 0.71, 0.58, 0.91);
        legend->SetFillColor(0);
        legend->SetFillStyle(0);
        legend->SetLineColor(0);
        legend->SetLineWidth(0);
        legend->SetTextSize(0.05);
        legend->SetTextFont(72);
        if (AddHeader)
        {
            legend->SetHeader(Headername);
        }
        legend->AddEntry(h1, legendname1, "lpfe");
        legend->AddEntry(h2, legendname2, "lpfe");
        legend->Draw("same");

        TPad *pad2;
        TH1D *h3;
        if (DoRatio)
        {
            // lower plot will be in pad
            c->cd(); // Go back to the main canvas before defining pad2
            pad2 = new TPad("pad2", "pad2", 0, 0, 1, 0.3);
            pad2->SetTopMargin(0);
            pad2->SetBottomMargin(0.3);
            pad2->SetLeftMargin(0.15);
            pad2->SetRightMargin(0.05);
            pad2->SetGridx(); // vertical grid
            pad2->SetGridy();
            pad2->Draw();
            pad2->cd(); // pad2 becomes the current pad

            // Define the ratio plot
            h3 = (TH1D *)h1->Clone("h3");
            h3->SetLineColor(kBlack);
            h3->SetStats(0); // No statistics on lower plot
            h3->Divide(h2);

            h3->GetYaxis()->SetRangeUser(1 - 0.15 - ratiorangeadd / 2,
                                         1 + 0.15 + ratiorangeadd / 2);

            h3->Draw("E0"); // Draw the ratio plot

            TF1 *referline = new TF1("referline", "1*x/x", minX, maxX);
            referline->Draw("same");
        }
        else if (DoDelta)
        {
            // lower plot will be in pad
            c->cd(); // Go back to the main canvas before defining pad2
            pad2 = new TPad("pad2", "pad2", 0, 0, 1, 0.3);
            pad2->SetTopMargin(0);
            pad2->SetBottomMargin(0.3);
            pad2->SetLeftMargin(0.15);
            pad2->SetRightMargin(0.05);
            pad2->SetGridx(); // vertical grid
            pad2->SetGridy();
            pad2->Draw();
            pad2->cd(); // pad2 becomes the current pad

            // Define the ratio plot
            h3 = (TH1D *)h1->Clone("h3");
            h3->SetLineColor(kBlack);
            h3->SetStats(0); // No statistics on lower plot
            h3->Add(h2, -1);

            h3->GetYaxis()->SetRangeUser(0 - 0.15 - ratiorangeadd / 2,
                                         0 + 0.15 + ratiorangeadd / 2);

            h3->Draw("E0"); // Draw the ratio plot

            TF1 *referline = new TF1("referline", "x-x", minX, maxX);
            referline->Draw("same");
        }
        else if (DoChi2)
        {
            // lower plot will be in pad
            c->cd(); // Go back to the main canvas before defining pad2
            pad2 = new TPad("pad2", "pad2", 0, 0, 1, 0.3);
            pad2->SetTopMargin(0);
            pad2->SetBottomMargin(0.3);
            pad2->SetLeftMargin(0.15);
            pad2->SetRightMargin(0.05);
            pad2->SetGridx(); // vertical grid
            pad2->SetGridy();
            pad2->Draw();
            pad2->cd(); // pad2 becomes the current pad

            h3 = (TH1D *)h1->Clone("h3");
            h3->Divide(h2);

            double Chi2_sum = 0;
            double maxchi2 = 0;

            for (int ibin = h1->FindBin(minX); ibin < h1->FindBin(maxX); ibin++)
            {
                double Nh1, Nh2, Nh1_err, Nh2_err;

                Nh1 = h1->GetBinContent(ibin);
                Nh2 = h2->GetBinContent(ibin);
                Nh1_err = h1->GetBinError(ibin);
                Nh2_err = h2->GetBinError(ibin);

                Chi2_sum = Chi2_sum + (Nh1 - Nh2) * (Nh1 - Nh2) /
                                          (Nh1_err * Nh1_err + Nh2_err * Nh2_err);

                if (DoPull)
                    h3->SetBinContent(
                        ibin, (Nh1 - Nh2) / sqrt(Nh1_err * Nh1_err + Nh2_err * Nh2_err));
                else
                    h3->SetBinContent(ibin, (Nh1 - Nh2) * (Nh1 - Nh2) /
                                                (Nh1_err * Nh1_err + Nh2_err * Nh2_err));
                h3->SetBinError(ibin, 0);

                if ((Nh1 - Nh2) * (Nh1 - Nh2) /
                        (Nh1_err * Nh1_err + Nh2_err * Nh2_err) >
                    maxchi2)
                    maxchi2 = (Nh1 - Nh2) * (Nh1 - Nh2) /
                              (Nh1_err * Nh1_err + Nh2_err * Nh2_err);
            }

            h3->SetLineColor(kBlack);
            h3->SetStats(0); // No statistics on lower plot

            if (DoPull)
                h3->GetYaxis()->SetRangeUser(-2.5, 2.5);
            else
                h3->GetYaxis()->SetRangeUser(0, maxchi2 + 0.3);

            h3->Draw("E0"); // Draw the ratio plot

            TF1 *referline;
            if (DoPull)
                referline = new TF1("referline", "x-x", minX, maxX);
            else
                referline = new TF1("referline", "1*x/x", minX, maxX);
            if (DoPull || (Chi2_sum / (h1->FindBin(maxX) - h1->FindBin(minX)) < 2))
                referline->Draw("same");

            pad1->cd();

            TLegend *Chi2legend = new TLegend(0.08, 0.61, 0.48, 0.71);
            Chi2legend->SetFillColor(0);
            Chi2legend->SetFillStyle(0);
            Chi2legend->SetLineColor(0);
            Chi2legend->SetLineWidth(0);
            Chi2legend->SetTextSize(0.05);
            Chi2legend->SetTextFont(72);

            char Chi2text[100];
            sprintf(Chi2text, "#frac{#chi^{2}}{NDF} = #frac{%.2f}{%d} = %.2f",
                    Chi2_sum, h1->FindBin(maxX) - h1->FindBin(minX),
                    Chi2_sum / (h1->FindBin(maxX) - h1->FindBin(minX)));
            Chi2legend->AddEntry((TObject *)0, Chi2text, "");
            Chi2legend->Draw("same");
        }

        // h1 settings
        h1->SetLineColor(kBlue + 1);
        h1->SetLineWidth(2);

        // Y axis h1 plot settings
        h1->GetYaxis()->SetTitleSize(35);
        h1->GetYaxis()->SetTitleFont(73);
        h1->GetYaxis()->SetTitleOffset(2.2 + move);
        h1->GetYaxis()->SetLabelSize(35);
        h1->GetYaxis()->SetLabelFont(73);

        // h2 settings
        h2->SetLineColor(kRed);
        h2->SetLineWidth(2);
        if (DoRatio)
        {
            // Ratio plot (h3) settings
            h3->SetTitle(""); // Remove the ratio title
            h3->SetLineWidth(2);

            char Rationame[100];
            sprintf(Rationame, "Ratio = #frac{%s}{%s}", legendname1, legendname2);
            // Y axis ratio plot settings
            h3->GetYaxis()->SetTitle(Rationame);
            h3->GetYaxis()->SetNdivisions(505);
            h3->GetYaxis()->SetTitleSize(35);
            h3->GetYaxis()->SetTitleFont(73);
            h3->GetYaxis()->SetTitleOffset(2);
            h3->GetYaxis()->SetLabelFont(
                73); // Absolute font size in pixel (precision 3)
            h3->GetYaxis()->SetLabelSize(35);

            // X axis ratio plot settings
            h3->GetXaxis()->SetTitleSize(35);
            h3->GetXaxis()->SetTitleFont(73);
            h3->GetXaxis()->SetTitleOffset(4.);
            h3->GetXaxis()->SetLabelFont(
                73); // Absolute font size in pixel (precision 3)
            h3->GetXaxis()->SetLabelSize(35);

            h3->GetXaxis()->SetTitle(Xtitle);
        }
        else if (DoDelta)
        {
            // Ratio plot (h3) settings
            h3->SetTitle(""); // Remove the ratio title
            h3->SetLineWidth(2);

            char Rationame[100];
            sprintf(Rationame, "#Delta = %s - %s", legendname1, legendname2);
            // Y axis ratio plot settings
            h3->GetYaxis()->SetTitle(Rationame);
            h3->GetYaxis()->SetNdivisions(505);
            h3->GetYaxis()->SetTitleSize(35);
            h3->GetYaxis()->SetTitleFont(73);
            h3->GetYaxis()->SetTitleOffset(2);
            h3->GetYaxis()->SetLabelFont(
                73); // Absolute font size in pixel (precision 3)
            h3->GetYaxis()->SetLabelSize(35);

            // X axis ratio plot settings
            h3->GetXaxis()->SetTitleSize(35);
            h3->GetXaxis()->SetTitleFont(73);
            h3->GetXaxis()->SetTitleOffset(4.);
            h3->GetXaxis()->SetLabelFont(
                73); // Absolute font size in pixel (precision 3)
            h3->GetXaxis()->SetLabelSize(35);

            h3->GetXaxis()->SetTitle(Xtitle);
        }
        else if (DoChi2)
        {
            // Ratio plot (h3) settings
            h3->SetTitle(""); // Remove the ratio title
            h3->SetLineWidth(2);

            char Chi2name[100];
            if (DoPull)
                sprintf(Chi2name, "#frac{#Delta}{#sigma}");
            else
                sprintf(Chi2name, "#chi^{2}");
            // Y axis ratio plot settings
            h3->GetYaxis()->SetTitle(Chi2name);
            h3->GetYaxis()->SetNdivisions(505);
            h3->GetYaxis()->SetTitleSize(35);
            h3->GetYaxis()->SetTitleFont(73);
            h3->GetYaxis()->SetTitleOffset(2);
            h3->GetYaxis()->SetLabelFont(
                73); // Absolute font size in pixel (precision 3)
            h3->GetYaxis()->SetLabelSize(35);

            // X axis ratio plot settings
            h3->GetXaxis()->SetTitleSize(35);
            h3->GetXaxis()->SetTitleFont(73);
            h3->GetXaxis()->SetTitleOffset(4.);
            h3->GetXaxis()->SetLabelFont(
                73); // Absolute font size in pixel (precision 3)
            h3->GetXaxis()->SetLabelSize(35);

            h3->GetXaxis()->SetTitle(Xtitle);
        }
        else
        {
            pad1->SetBottomMargin(0.15);

            h1->GetXaxis()->SetTitle(Xtitle);
            h1->GetXaxis()->SetTitleSize(35);
            h1->GetXaxis()->SetTitleFont(73);
            h1->GetXaxis()->SetTitleOffset(1.1);
            h1->GetXaxis()->SetLabelFont(
                73); // Absolute font size in pixel (precision 3)
            h1->GetXaxis()->SetLabelSize(35);

            h1->GetYaxis()->SetTitleOffset(1.4);
        }
        if (DoSave)
            c->SaveAs(savefilename);
    }
    else
    {
        TFile *file1 = new TFile(filename1);

        TH1D *h1 = (TH1D *)file1->Get(plotname1);

        if (DoRebin)
            h1->Rebin(RebinNumber1);

        if (SetXRange)
            h1->GetXaxis()->SetRangeUser(minX, maxX);

        double minY, maxY, left;
        minY = h1->GetMinimum();
        maxY = h1->GetMaximum();
        left = (maxY - minY) * 0.025;

        // if(minY-left<0&&minY>=0)
        // h1->GetYaxis()->SetRangeUser(0.01,maxY+left);
        // else
        h1->GetYaxis()->SetRangeUser(minY - left, maxY + left);

        TCanvas *c = new TCanvas("c", "canvas", 1000, 700);

        // plot will be in pad1
        TPad *pad1 = new TPad("pad1", "pad1", 0, 0, 1, 1.0);
        pad1->SetGrid(gridx, gridy); // Vertical grid
        pad1->SetTopMargin(0.07);
        pad1->SetBottomMargin(0.15);
        pad1->SetLeftMargin(0.15);
        pad1->SetRightMargin(0.05);
        pad1->Draw();    // Draw the upper pad: pad1
        pad1->cd();      // pad1 becomes the current pad
        h1->SetStats(0); // No statistics on upper plot
        h1->Draw("E0");  // Draw h1

        h1->GetYaxis()->SetLabelSize(0.05);
        h1->GetYaxis()->SetLabelFont(72);
        h1->GetXaxis()->SetLabelSize(0.05);
        h1->GetXaxis()->SetLabelFont(72);

        h1->GetYaxis()->SetTitle(Ytitle);
        h1->SetTitle("");

        // h1 settings
        h1->SetLineColor(kBlue + 1);
        h1->SetLineWidth(2);

        // Y axis h1 plot settings
        h1->GetYaxis()->SetTitleSize(35);
        h1->GetYaxis()->SetTitleFont(73);
        h1->GetYaxis()->SetTitleOffset(1.4 + move);
        h1->GetXaxis()->SetTitle(Xtitle);
        h1->GetXaxis()->SetTitleSize(35);
        h1->GetXaxis()->SetTitleFont(73);
        h1->GetXaxis()->SetTitleOffset(1.1);

        if (AddHeader)
        {
            TLegend *legend = new TLegend(0.18, 0.84, 0.58, 0.94);
            legend->SetFillColor(0);
            legend->SetFillStyle(0);
            legend->SetLineColor(0);
            legend->SetLineWidth(0);
            legend->SetTextSize(0.05);
            legend->SetTextFont(72);
            legend->SetHeader(Headername);
            legend->Draw("same");
        }

        if (DoSave)
            c->SaveAs(savefilename);
    }
}
