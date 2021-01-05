#include "MyCNN.h"
#include "Data.hpp"
#include <bits/stdc++.h>

using namespace std;
using namespace myCnn;

int main()
{
    /*
    try
    {
        Matrix A = FileLoader("/home/invrise/SleepWalker/Assignment/C++/Project2/build/face.jpg").data;
        A.display();

        Layer* relu = new ReLU(0);
        Layer* pool = new Pool<MAX>(2, 2);

        Layer* conv0 = new Convolution(2, Matrix({16, 3}, 3, conv0_weight), Matrix({16, 1}, 1, conv0_bias), 1);
        dynamic_cast<Convolution*>(conv0)->setChannelDimension(1);
        conv0->execute(A);
        relu->execute(conv0->getResult());
        pool->execute(relu->getResult());

        Matrix B = pool->getResult();
        B.redimension();
        B.display();

        Layer* conv1 = new Convolution(1, Matrix({32, 16}, 3, conv1_weight), Matrix({32, 1}, 1, conv1_bias), 0);
        dynamic_cast<Convolution*>(conv1)->setChannelDimension(1);
        conv1->execute(B);
        relu->execute(conv1->getResult());
        pool->execute(relu->getResult());

        Matrix C = pool->getResult();
        C.redimension();
        C.display();


        Layer* conv2 = new Convolution(2, Matrix({32, 32}, 3, conv2_weight), Matrix({32, 1}, 1, conv2_bias), 1);
        dynamic_cast<Convolution*>(conv2)->setChannelDimension(1);
        conv2->execute(C);
        relu->execute(conv2->getResult());

        Matrix D = relu->getResult();
        D.redimension();
        D.display();

        Layer* fc = new FullyConnection(Data(fc0_weight), Size(2, 2048), Data(fc0_bias), Size(2, 1));
        fc->execute(D);

        Matrix E = fc->getResult();

        cout.precision(numeric_limits<float>::max_digits10);
        cout << fixed << E({0, 0}, 0, 0) << endl << E({1, 0}, 0, 0) << endl;

        delete relu;
        delete pool;
        delete conv0;
        delete conv1;
        delete conv2;
    }
    catch (const char* error)
    {
        cerr << error << endl;
    }
    */

    try
    {
        Matrix background = FileLoader("/home/invrise/SleepWalker/Assignment/C++/Project2/build/bg.jpg");
        Matrix face = FileLoader("/home/invrise/SleepWalker/Assignment/C++/Project2/build/face.jpg");
        Matrix background2 = FileLoader("/home/invrise/SleepWalker/Assignment/C++/Project2/build/bg2.jpg");
        Matrix face2 = FileLoader("/home/invrise/SleepWalker/Assignment/C++/Project2/build/face2.jpg");
        Matrix bg3 = FileLoader("/home/invrise/SleepWalker/Assignment/C++/Project2/build/bg3.jpg");
        Process process;

        StepLayer conv0(new Convolution(2, Matrix({16, 3}, 3, conv0_weight), Matrix({16, 1}, 1, conv0_bias), 1));
        StepLayer conv1(new Convolution(1, Matrix({32, 16}, 3, conv1_weight), Matrix({32, 1}, 1, conv1_bias), 0));
        StepLayer conv2(new Convolution(2, Matrix({32, 32}, 3, conv2_weight), Matrix({32, 1}, 1, conv2_bias), 1));
        StepLayer relu(new ReLU(0));
        StepLayer pool(new Pool<MAX>(2, 2));
        StepLayer fc(new FullyConnection(Data(fc0_weight, 2 * 2048), Size(2, 2048), Data(fc0_bias, 2 * 1), Size(2, 1)));

        /*
        process.addStep(conv0);
        process.addStep(relu);
        process.addStep(pool);
        process.addStep(conv1);
        process.addStep(relu);
        process.addStep(pool);
        process.addStep(conv2);
        process.addStep(relu);
        process.addStep(fc);
        */

        process.addSteps({conv0, relu, pool, conv1, relu, pool, conv2, relu, fc});

        process.setLogLevel(PART);
        process.setChannelDimensions({1, 1, 1});

        cout.precision(8);
        
        /*
        process.execute(background);
        Matrix bg_result = process.getCurrentResult();
        cout << fixed << bg_result({0, 0}, 0, 0) << endl << bg_result({1, 0}, 0, 0) << endl;

        process.execute(face);
        Matrix face_result = process.getCurrentResult();
        cout << fixed << face_result({0, 0}, 0, 0) << endl << face_result({1, 0}, 0, 0) << endl;
        
        process.execute(background2);
        Matrix bg2_result = process.getCurrentResult();
        cout << fixed << bg2_result({0, 0}, 0, 0) << endl << bg2_result({1, 0}, 0, 0) << endl;

        process.execute(face2);
        Matrix face2_result = process.getCurrentResult();
        cout << fixed << face2_result({0, 0}, 0, 0) << endl << face2_result({1, 0}, 0, 0) << endl;

        process.execute(bg3);
        Matrix bg3_result = process.getCurrentResult();
        cout << fixed << bg3_result({0, 0}, 0, 0) << endl << bg3_result({1, 0}, 0, 0) << endl;
        */

        Matrix imageInfo = FileLoader("/home/invrise/SleepWalker/Assignment/C++/Project2/build/face_woman02.jpg");

        process.execute(imageInfo);
        Matrix imageInfoResult = process.getCurrentResult();
        cout << fixed << imageInfoResult({0, 0}, 0, 0) << endl << imageInfoResult({1, 0}, 0, 0) << endl;
    }
    catch(const char* error)
    {
        cerr << error << endl;
    }

    return 0;
}