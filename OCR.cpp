#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <random>
#include <string>

using namespace std;

struct RED {
    ///Pesos Wn[Neuronas capa anterior][Neuronas capa actual];
    double W12[784][50];
    double W23[50][50];
    double W34[50][10];
    ///Umbrales Un[Umbral de la neurona i de la capa N];
    double U2[50];
    double U3[50];
    double U4[10];
    ///Salidas de neurona An[Salida de la neurona i de la capa N];
    double E[784];
    double S[10];
    double Ent[784];
    double Sal[10];
    double Sal_obt[10];
    double A2[50];
    double A3[50];
    double A4[10];
    //----------------------------------------------------------------------
    //ENTRENAMIENTO;
    //----------------------------------------------------------------------
    ///Pesos Wn[Neuronas capa anterior][Neuronas capa actual];
    double WE12[784][50];
    double WE23[50][50];
    double WE34[50][10];
    ///Umbrales Un[Umbral de la neurona i de la capa N];
    double UE2[50];
    double UE3[50];
    double UE4[10];
    //----------------------------------------------------------------------
    //FUNCION DE ACTIVACION
    //----------------------------------------------------------------------
    double FuncionActivacion(double &SumPonderada){
    double Resultado;
    Resultado = 1/(1+exp(-SumPonderada));
    return Resultado;
    }
    //----------------------------------------------------------------------
    //Epocas
    //----------------------------------------------------------------------
    int Epoca;
};
void IniciarRed(RED& R){
    // Crear un generador de números aleatorios
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 0.1);

    // Crear las matrices y llenarlas con valores aleatorios

        for (int i = 0; i < 784; i++) {
            for (int j = 0; j < 50; j++) {
                R.W12[i][j] = dis(gen);
            }
        }
        for (int i = 0; i < 50; i++) {
            for (int j = 0; j < 50; j++) {
                R.W23[i][j] = dis(gen);
            }
        }
        for (int i = 0; i < 50; i++) {
            for (int j = 0; j < 10; j++) {
                R.W34[i][j] = dis(gen);
            }
        }
        /// Iniciar umbrales
        for (int j = 0; j < 50; j++) {
            R.U2[j] = dis(gen);
        }
        for (int j = 0; j < 50; j++) {
            R.U3[j] = dis(gen);
        }
        for (int j = 0; j < 10; j++) {
            R.U4[j] = dis(gen);
        }

        // Imprimir la matriz
        //std::cout << "Matriz " << k+1 << ":" << std::endl;
//        for (int i = 0; i < 784; i++) {
//            for (int j = 0; j < 16; j++) {
//                std::cout << R.W12[i][j] << " ";
//            }
//            std::cout << std::endl;
//        }
//        std::cout << std::endl;
//        for (int i = 0; i < 16; i++) {
//            for (int j = 0; j < 16; j++) {
//                std::cout << R.W23[i][j] << " ";
//            }
//            std::cout << std::endl;
//        }
//        std::cout << std::endl;
//        for (int i = 0; i < 16; i++) {
//            for (int j = 0; j < 10; j++) {
//                std::cout << R.W34[i][j] << " ";
//            }
//            std::cout << std::endl;
//        }
//        std::cout << std::endl;
//        for (int j = 0; j < 16; j++) {
//            cout << R.U2[j] << " ";
//        }cout << endl;
//        for (int j = 0; j < 16; j++) {
//            cout << R.U3[j] << " ";
//        }cout << endl;
//        for (int j = 0; j < 10; j++) {
//            cout << R.U4[j] << endl;
//        }cout << endl;
//        cout << endl << endl;
}
void Procesado_Feedforward(RED& R){
    ///Entra a la red la matriz de 28x28
    ///Se obtienen las salidas de la capa 2
    ///A[]=(W12[][])*(EntradaRED[]) + U[];
    double ValorSuma = 0;
    for(int i = 0; i < 50; i++){
        for(int j = 0; j< 784; j++){
            ValorSuma += R.E[j]*R.W12[j][i];
            //cout << R.E[j] << "*" << R.W12[j][i]
            //<<" + " << R.U2[i] << " = " << ValorSuma << endl;
        }
        ValorSuma += R.U2[i];
        R.A2[i] = R.FuncionActivacion(ValorSuma);
        //cout << ValorSuma << endl;
        //cout << R.FuncionActivacion(ValorSuma) << endl;
        //cout << "Salida de la neurona " << i << " de la capa 2:
        // " << R.A2[i] << endl;
        ValorSuma = 0;
    }
    ///Se obtienen las salidas de la capa 3
    ///A2[]=(W12[][])*(EntradaRED[]) + U[];
    ValorSuma = 0;
    for(int i = 0; i < 50; i++){
        for(int j = 0; j< 50; j++){
            ValorSuma += R.A2[j]*R.W23[j][i];
            //cout << ValorSuma <<endl;
        }
        ValorSuma += R.U3[i];
        R.A3[i] = R.FuncionActivacion(ValorSuma);
        //cout << ValorSuma << endl;
        //cout << R.FuncionActivacion(ValorSuma) << endl;
        //cout << "Salida de la neurona " << i << " de la capa 3:
        // " <<R.A3[i] << endl;
        ValorSuma = 0;
    }
    ///Se obtienen las salidas de la capa 4
    ///A2[]=(W12[][])*(EntradaRED[]) + U[];
    ValorSuma = 0;
    for(int i = 0; i < 50; i++){
        for(int j = 0; j< 50; j++){
            ValorSuma += R.A3[j]*R.W34[j][i];
        }
        ValorSuma += R.U4[i];
        R.A4[i] = R.FuncionActivacion(ValorSuma);
//        R.Sal[i] = R.A4[i];
        if(R.A4[i] > 0.5)
        {
            R.Sal[i] = 1;
        }
        else{
            R.Sal[i] = 0;
        }
        //cout << ValorSuma << endl;
        //cout << R.FuncionActivacion(ValorSuma) << endl;
        //cout << "Salida de la neurona " << i << " de la capa 3:
        // " << R.A4[i] << endl;
        ValorSuma = 0;
        }
        double Mayor = 0;
        int j = 0;
        for(int i = 0; i < 10; i++)
        {
            if(R.A4[i] > Mayor)
            {
                Mayor = R.A4[i];
            }
        }
        for(int j = 0; j < 10; j++)
        {
            if(R.A4[j] == Mayor)
            {
                R.Sal_obt[j] = 1;
            }else
            {
                R.Sal_obt[j] = 0;
            }
        }
    ValorSuma = 0;
}
void EntrenamientoRED(RED& R){
    double alpha = 0.00155;
    ///----------------------------------------------------------------------
    ///ENTRENAMIENTO PESOS 34
    ///----------------------------------------------------------------------
    for(int i = 0; i < 50; i++){
        for(int j = 0; j < 10; j++){
            double Yi = R.A4[j];
            double dE3 = (R.A3[i])*(Yi - R.S[j])*(Yi)*(1-Yi);
            R.WE34[i][j] = (R.W34[i][j]) - (alpha*dE3);
            //cout << "dE3: " <<dE3 << endl << "R.A4: " <<
            //R.A4[j] << endl << "R.S: " << R.S[j] << endl;
            //cout << "R.WE34 = (R.W34[i][j]) - (alpha*dE3) = "
            //<< R.WE34[i][j] << " R.W34[i][j]: " << R.W34[i][j] << endl;
        }
    }
    ///----------------------------------------------------------------------
    ///ENTRENAMIENTO PESOS 23
    ///----------------------------------------------------------------------
    for(int i = 0; i < 50; i++){
        for(int j = 0; j < 50; j++){
            double acumulador;
            for(int k = 0; k < 10; k++)
            {
                double Yi = R.A4[k];
                acumulador += R.W23[j][k] * (Yi - R.S[k]) * Yi * (1 - Yi);
            }
        double dE2 = R.A2[i] * R.A3[j] * (1 - R.A3[j]) * acumulador;
        R.WE23[i][j] = R.W23[i][j] - alpha * dE2;
        }
    }
    ///----------------------------------------------------------------------
    ///ENTRENAMIENTO PESOS 12
    ///----------------------------------------------------------------------
    for (int p = 0; p < 784; p++){
        for (int i = 0; i < 50; i++){
            double acm1 = 0;
            for (int j = 0; j < 50; j++){
                double acm2 = 0;
                for(int k = 0; k < 10; k++){
                    double Yk = R.A4[k];
                    acm2 += R.W34[j][k]*(Yk-R.S[k])*(1-Yk);
                }acm1 += R.W23[i][j]*R.A3[j]*(1-R.A3[j])*acm2;
            }double dE1 = R.E[p]*R.A2[i]*(1-R.A2[i])*acm1;
            R.WE12[p][i] = R.W12[p][i] - alpha*dE1;
        }
    }
    ///----------------------------------------------------------------------
    ///ENTRENAMIENTO UMBRALES 4
    ///----------------------------------------------------------------------
    for (int i = 0; i < 10; i++){
        double Yi = R.A4[i];
        double dEU4 = (Yi - R.S[i])*Yi*(1-Yi);
        R.UE4[i] = R.U4[i] - alpha*dEU4;
    }
    ///----------------------------------------------------------------------
    ///ENTRENAMIENTO UMBRALES 3
    ///----------------------------------------------------------------------
    for (int i = 0; i < 50; i++){
        double acm = 0;
        for(int j = 0; j < 10; j++){
            double Yi = R.A4[j];
            acm += R.W34[i][j]*(Yi - R.S[j])*Yi*(1-Yi);
        }
        double dEU3 = R.A3[i]*(1-R.A3[i])*acm;
        R.UE3[i] = R.U3[i] - alpha*dEU3;
    }
    ///----------------------------------------------------------------------
    ///ENTRENAMIENTO UMBRALES 2
    ///----------------------------------------------------------------------
    for (int i = 0; i < 50; i++){
        double acm = 0;
        for(int j = 0; j < 50; j++){
            double acm1 = 0;
            for (int p = 0; p < 10; p++){
                double Yi = R.A4[p];
                acm1 += R.W34[j][p]*(Yi - R.S[p])*Yi*(1-Yi);
            }
            acm += R.W23[i][j]*R.A3[j]*(1-R.A3[j])*acm1;
        }
        double dEU2 = R.A2[i]*(1-R.A2[i])*acm;
        R.UE2[i] = R.U2[i] - alpha*dEU2;
    }
    ///----------------------------------------------------------------------
    ///COPIAR LOS NUEVOS PESOS Y UMBRALES
    ///----------------------------------------------------------------------
    ///----------------------------------------------------------------------
    ///COPIA LOS NUEVOS PESOS W34
    ///----------------------------------------------------------------------
    for (int i = 0; i < 50; i++){
        for (int j = 0; j < 10; j++){
            R.W34[i][j] = R.WE34[i][j];
        }
    }
    ///----------------------------------------------------------------------
    ///COPIA LOS NUEVOS PESOS W23
    ///----------------------------------------------------------------------
    for (int i = 0; i < 50; i++){
        for (int j = 0; j < 50; j++){
            R.W23[i][j] = R.WE23[i][j];
        }
    }
    ///----------------------------------------------------------------------
    ///COPIA LOS NUEVOS PESOS W12
    ///----------------------------------------------------------------------
    for (int i = 0; i < 50; i++){
        for (int j = 0; j < 784; j++){
            R.W12[i][j] = R.WE12[i][j];
        }
    }
    ///----------------------------------------------------------------------
    ///COPIA LOS NUEVOS UMBRALES DE LA CAPA 4
    ///----------------------------------------------------------------------
    for (int i = 0; i < 10; i++){
        R.U4[i] = R.UE4[i];
    }
    ///----------------------------------------------------------------------
    ///COPIA LOS NUEVOS UMBRALES DE LA CAPA 3
    ///----------------------------------------------------------------------
    for (int i = 0; i < 50; i++){
        R.U3[i] = R.UE3[i];
    }
    ///----------------------------------------------------------------------
    ///COPIA LOS NUEVOS UMBRALES DE LA CAPA 2
    ///----------------------------------------------------------------------
    for (int i = 0; i < 50; i++){
        R.U2[i] = R.UE2[i];
    }
}
void Reajuste_pesos(RED& R){
    for(int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << R.W12[i][j]<< " ";
        }
        cout << endl;
    }
    cout << endl;
    for(int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << R.W23[i][j]<< " ";
        }
        cout << endl;
    }
    cout << endl;
    for(int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            cout << R.W34[i][j] << " ";
        }
        cout << endl;
    }cout << endl;
}
void Muestra_PYU(RED& R)
{
    cout << "Pesos: " << endl;
    for(int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            cout << R.W23[i][j];

        }cout << endl;
    }
    cout << endl << endl << "Umbrales: " << endl;;
    for(int i = 0; i < 10; i++)
    {
        cout << R.U4[i];
    }
}
void OpenCSV(RED& R){
    ifstream archivoCSV;
    string linea;
    archivoCSV.open("mnist_train.csv", ios::in);
    if(!archivoCSV.is_open()){
        cout << "Error. El archivo no se ha abierto. " << endl;
    }
    getline(archivoCSV, linea); /// omitir la primera línea que contiene
    ///encabezados
    while(getline(archivoCSV,linea)){
        string etiqueta_string = linea.substr(0, linea.find(","));
        int etiqueta = stoi(etiqueta_string);
        //cout << endl << endl;
        //cout << "Etiqueta: " << etiqueta << endl;
        for(int i = 0; i < 10; i++)
        {
            if(i == etiqueta)
            {
                R.S[i] = 1;
            }else{
                R.S[i] = 0;
            }
        }
        stringstream registro(linea);
        string componente ;
        double comp;
        double valor;
        int contador = 0;
        getline(registro, componente, ',');
        while (getline(registro, componente, ',')) {
            comp = stoi(componente);
            valor = (comp)/(255);
//            if(comp > 0){
//                comp = 1;
//            }
            R.Ent[contador] = valor;
//           cout << valor << " ";
           contador++;
//            if(contador%28 == 0){
//                cout << endl;
//            }
        }
        contador = 0;
        //cout << endl;
        Procesado_Feedforward(R);
        //Muestra_PYU(R);
        //cout << endl;
        EntrenamientoRED(R);
        //cout << "Nuevos pesos: ";
        //Muestra_PYU(R);
        if(R.Epoca % 2 == 0)
        {
            cout << endl<<"Epoca: "<< R.Epoca << endl;
//            cout << endl << " Muestra: " << Muestra;
             cout << endl;
        cout << "Entrada: " << etiqueta << endl;
        cout << "Salida esperada: ";
        for(int i = 0; i < 10; i++)
        {
            cout << R.S[i] << ", ";
        }
        cout << endl;
        cout << "Salida obtenida: ";
        for(int i = 0; i < 10; i++)
        {
            cout << R.Sal_obt[i] << ", ";
        }
        cout << endl;
        cout << "Salida real: ";
        for(int i = 0; i < 10; i++)
        {
            cout << R.A4[i] << ", ";
        }
        cout << endl;
        }
//        Muestra++;
    }
//    Muestra = 0;
//    cout << " FIN ";

    archivoCSV.close();
}
void EntrenaRed(RED& R)
{
    R.Epoca = 0;
    while (R.Epoca < 10000)
    {
        OpenCSV(R);
        R.Epoca++;
        if(R.Epoca>9999)
        {
            cout << "FIN";
        }
    }
}
int main(){
    RED R;
    IniciarRed(R);
    EntrenaRed(R);
}
