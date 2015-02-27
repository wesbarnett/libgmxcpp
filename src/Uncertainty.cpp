
#include "gmxcpp/Uncertainty.h"

vector <double> bootstrap(int boot_n, int block_n, vector < vector <double> >& data, int frame_count)
{

	const int data_size = data.at(0).size();
    const int block_frames = frame_count / block_n;
    int boot_i;
    int i;

    vector <double> avg(data_size,0.0);
    vector <double> var(data_size,0.0);
    vector <double> uncertainty(data_size);
    vector < vector <double> > values(boot_n,vector<double>(data_size));

    #pragma omp parallel
    {

    int block;
    int block_end;
    int boot_i;
    int block_i;
    int frame_i;
    int i;

    #pragma omp for
    for (boot_i = 0; boot_i < boot_n; boot_i++)
    {
		for (i = 0; i < data_size; i++)
		{
		    values.at(boot_i).at(i) = 0.0;
	    }

        for (block_i = 0; block_i < block_n; block_i++)
        {

            block = rand() % block_n;

            if (block == block_n-1)
            {
                block_end = frame_count;
            }
            else
            {
                block_end = (block+1)*block_frames;
            }

            for (frame_i = block*block_frames; frame_i < block_end; frame_i++)
            {

				for (i = 0; i < data_size; i++)
				{
					values.at(boot_i).at(i) += data.at(frame_i).at(i);
				}
            }

        }

		for (i = 0; i < data_size; i++) 
		{
			values.at(boot_i).at(i) /= ((double)(frame_count));
		}

		for (i = 0; i < data_size; i++) 
		{
			avg.at(i) += values.at(boot_i).at(i);
		}
    }

    }

	for (i = 0; i < data_size; i++) 
	{
		avg.at(i) /= (double) boot_n;
	}

    for (boot_i = 0; boot_i < boot_n; boot_i ++)
    {
		for (i = 0; i < data_size; i++) 
		{
			var.at(i) += pow(avg.at(i) - values.at(boot_i).at(i),2);
		}
    }

	for (i = 0; i < data_size; i++) 
	{
		var.at(i) /= (double) (boot_n-1);
		uncertainty.at(i) = sqrt(var.at(i));
	}

	return uncertainty;

}


double bootstrap(int boot_n, int block_n, vector <double> & data, int frame_count)
{

    const int block_frames = frame_count / block_n;
    double avg;
    double var;
    double uncertainty;
    int boot_i;
    vector <double> values(boot_n,0.0);

    #pragma omp parallel
    {

    int block;
    int block_end;
    int boot_i;
    int block_i;
    int frame_i;

    #pragma omp for
    for (boot_i = 0; boot_i < boot_n; boot_i++)
    {

        for (block_i = 0; block_i < block_n; block_i++)
        {

            block = rand() % block_n;

            if (block == block_n-1)
            {
                block_end = frame_count;
            }
            else
            {
                block_end = (block+1)*block_frames;
            }

            for (frame_i = block*block_frames; frame_i < block_end; frame_i++)
            {

				values.at(boot_i) += data.at(frame_i);
            }

        }

		values.at(boot_i) /= ((double)(frame_count));
		avg += values.at(boot_i);
    }

    }

	avg /= (double) boot_n;

    for (boot_i = 0; boot_i < boot_n; boot_i ++)
    {
		var += pow(avg - values.at(boot_i),2);
    }

	var /= (double) (boot_n-1);
	uncertainty = sqrt(var);

	return uncertainty;

}

