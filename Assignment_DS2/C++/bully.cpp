#include"process.cpp"
using namespace std;

string sendMessage(Process receiver){
    return receiver.processMessage();
}

int main(){
    float processProbability;
    cout<<"Enter active process probability: ";
    cin>>processProbability;
    Process::ACTIVE_PROB = processProbability;

    int processPoolSize;
    cout<<"Enter process pool size: ";
    cin>>processPoolSize;
    vector<Process> processPool;
    for(int i=0;i<processPoolSize;i++){
        processPool.push_back(Process(i));
    }
    srand(time(NULL));
    processPool[rand() % processPoolSize].coordinate = true;

    for(int i=0;i<100;i++){
        int p1Index = rand() % processPoolSize;
        int p2Index = rand() % processPoolSize;

        if(p1Index == p2Index) continue;

        Process p1 = processPool[p1Index];
        Process p2 = processPool[p2Index];
        string response = sendMessage(p2);
        cout<<"Process "<<p1.identifier<<" Process "<<p2.identifier<<" talking..."<<endl;

        if(response == "NOT_OK" && p2.coordinate){
            cout<<"Coordinator process"<<p2.identifier<<" not responding. Holding election..."<<endl;
            vector<Process> higherProcesses(processPool.begin() + p1Index + 1, processPool.end());

            for(Process p : higherProcesses){
                cout<<"Sent ELECTION message to process"<<p.identifier<<endl;
                response = sendMessage(p);

                if(response == "OK"){
                    cout<<"New Coordinator chosen as process"<<p.identifier<<endl;
                    p.coordinate = true;
                    break;
                }
                else{
                    cout<<"Negative response from process"<<p.identifier<<endl;
                }
            } 
            p2.coordinate = false;
        }
    }

    return 0;
}