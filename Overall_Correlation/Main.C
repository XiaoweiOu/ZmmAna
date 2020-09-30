#include "State.h"

int main(int argc, char **argv)
{

    ZRapidityOverall = new CorrelationTool(true, true, true, true);
    ZRapidityOverall->Initialize();

    for (int i = 0; i < 100; i++)
        ZRapidityOverall->CallRandomExperiment();

    ZRapidityOverall->CalculateCorrelation();
    ZRapidityOverall->SaveFigure("OverallCorrelation_Matrix.eps");
    ZRapidityOverall->SaveFigureFB("OverallCorrelation_FBMatrix.eps");
    ZRapidityOverall->SaveFile();

    return 0;
}
