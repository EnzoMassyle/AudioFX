#include "eq.h"

EQ::EQ(int sr)
{
    this->filters = new Biquad*[NUM_FILTERS];

    assert(this->filters != nullptr);
    this->sampleRate = sr;
    for (int i = 0; i < NUM_GAIN_FILTERS; i++)
    {
        this->gains[i] = 0.0;
    }
    this->addFilters();
}

EQ::EQ(int sr, double g[], int lenG)
{
    this->filters = new Biquad*[NUM_FILTERS];
    assert(this->filters != nullptr);
    assert(lenG == NUM_GAIN_FILTERS);

    for (int i = 0; i < NUM_GAIN_FILTERS; i++)
    {
        this->gains[i] = g[i];
    }
    this->addFilters();
    
}

void EQ::addFilters()
{
    assert(this->filters != nullptr);
    this->filters[0] = new HighPass(20, this->sampleRate, 0.707); 
    this->filters[1] = new LowShelf(this->gains[0], 75, this->sampleRate, 1.0);
    this->filters[2] = new BellFilter(this->gains[1], 100, this->sampleRate, 0.6);
    this->filters[3] = new BellFilter(this->gains[2], 250, this->sampleRate, 0.3);
    this->filters[4] = new BellFilter(this->gains[3], 1040, this->sampleRate, 0.4);
    this->filters[5] = new BellFilter(this->gains[4], 2500, this->sampleRate, 0.2);
    this->filters[6] = new HighShelf(this->gains[5], 7500, this->sampleRate, 1.0);
    this->filters[7] = new LowPass(20000, this->sampleRate, 0.707);
}


EQ::~EQ()
{
    for (int i = 0; i < NUM_FILTERS; i++)
    {
        delete this->filters[i];
    }
    delete[] this->filters;
}

void EQ::applyEQ(vector<vector<double>> &samples)
{
    for (int i = 0; i < NUM_FILTERS; i++)
    {
        this->filters[i]->process(samples);
    }
}