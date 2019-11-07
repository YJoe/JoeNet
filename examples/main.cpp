#include<iostream>
#include<vector>
#include<stdlib.h>

#include "neural_network.h"

int main() {

    // creating an input data set
    std::vector<std::vector<float>> training_inputs;
    for (int i = 0; i < 1000000; i++) {
        std::vector<float> data;
        data.push_back(static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
        data.push_back(static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
        training_inputs.push_back(data);
    }

    // get the outputs for that data set
    std::vector<std::vector<float>> training_outputs;
    for (int i = 0; i < training_inputs.size(); i++) {
        std::vector<float> output;
        float sum = 0.0f;
        for (int j = 0; j < 2; j++){
            sum += training_inputs[i][j];
        }
        output.push_back(sum);
        training_outputs.push_back(output);
    }

    // creating the network from 2 input neurons, 3 hidden neurons and 1 output
    std::vector<int> topology = {2, 3, 1};
    NeuralNetwork n = NeuralNetwork(&topology, 0.1);

    // training the network
    for (int i = 0; i < training_inputs.size(); i++) {

        // tell the net to do the sum
        n.feed_forward(&training_inputs[i]);

        // tell it how far off it was
        n.backwards_propagate(&training_outputs[i]);
    }

    // test the network on this input
    std::vector<float> input = {0.3, 0.5};
    n.feed_forward(&input);
    std::vector<float> results;
    n.get_results(results);
    std::cout << "for the input [ ";
    for (int i = 0; i < input.size(); i++) {
        std::cout << input[i] << " ";
    }
    std::cout << "] the result was [ ";
    for (int i = 0; i < results.size(); i++){
        std::cout << results[i] << " ";
    }
    std::cout << "]" << std::endl;
}