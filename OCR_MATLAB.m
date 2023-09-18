%Autor: Miguel Ángel Linares Hernández
%TFG: Implementación de una red neuronal para el reconocimiento 
%     de caracteres escritos a mano en una FPGA.
%Implementación de la red con MATLAB

Dir_MNIST = 'C:\Users\migue\Documents\MATLAB';
imD = imageDatastore(Dir_MNIST,'IncludeSubfolders',true,'LabelSource','foldernames');
figure
Im_totales = 10000;
perm = randperm(Im_totales,20);
for i = 1:20
    subplot(4,5,i);
    imshow(imD.Files{perm(i)});
    drawnow;
end

numTrainingFiles = 750;
[imdsTrain,imdsTest] = splitEachLabel(imD,numTrainingFiles,'randomize');


layers = [
    imageInputLayer([28 28 1]) % Capa de entrada para imágenes de 28x28 píxeles en escala de grises
    fullyConnectedLayer(50)     % Primera capa oculta con 16 neuronas
    sigmoidLayer                % Función de activación Sigmoide en la primera capa oculta
    fullyConnectedLayer(50)     % Segunda capa oculta con 16 neuronas
    sigmoidLayer                % Función de activación Sigmoide en la segunda capa oculta
    fullyConnectedLayer(10)     % Capa de salida con 10 neuronas (una por cada dígito del 0 al 9)
    softmaxLayer                % Función de activación Softmax en la capa de salida para clasificación
    classificationLayer()       % Capa de clasificación para calcular la pérdida y métricas de clasificación
];

options = trainingOptions('sgdm', ...
    'MaxEpochs',2500,...
    'InitialLearnRate',1e-4, ...
    'Verbose',false, ...
    'Plots','training-progress');
%view(net);
net = trainNetwork(imdsTrain,layers,options);
% Supongamos que 'net' es tu red neuronal ya entrenada con la estructura 784x50x50x10

% Obtener los pesos y umbrales por capa
pesos_por_capa = cell(length(net.Layers)-1, 1);
umbrales_por_capa = cell(length(net.Layers)-1, 1);

for i = 1:(length(net.Layers)-1)
    % Obtener los pesos y umbrales de la capa 'i'
    capa = net.Layers(i+1);
    pesos_por_capa{i} = capa.Weights;
    umbrales_por_capa{i} = capa.Bias;
end

% Nombre del archivo donde se guardarán los pesos y umbrales
nombre_archivo = 'pesos_umbrales_por_capa.mat';

% Guardar los pesos y umbrales por capa en el archivo
save(nombre_archivo, 'pesos_por_capa', 'umbrales_por_capa');

% Mensaje de confirmación
disp(['Pesos y umbrales por capa guardados en ' nombre_archivo]);

