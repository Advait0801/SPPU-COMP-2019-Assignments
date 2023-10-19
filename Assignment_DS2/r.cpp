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
            
            Process initiator = processPool[p1Index];
            initiator.coordinate = false;

            vector<Process> processList;
            int counter = p1Index + 1;
            Process currProcess = processPool[counter];

            while(currProcess.identifier != initiator.identifier){
                cout<<"Sent ELECTION message to process"<<currProcess.identifier<<endl;
                response = sendMessage(currProcess);

                if(response == "OK"){
                    processList.push_back(currProcess);
                    cout<<"Positive response from process"<<currProcess.identifier<<". Adding to message list..."<<endl;
                }
                else{
                    cout<<"Negative response from process"<<currProcess.identifier<<". Skipped.."<<endl;
                }

                counter = (counter + 1) % processPoolSize;
                currProcess = processPool[counter];
            } 

            auto maxIdentifierProcessIterator = std::max_element(processList.begin(), processList.end(), [](const Process &p1,const Process &p2){
                return p1.identifier < p2.identifier;
            }); 
            Process maxIdentifierProcess = processPool[maxIdentifierProcessIterator - processPool.begin()];
            maxIdentifierProcess.coordinate = true;
            cout<<"Max Identifier process is process"<<maxIdentifierProcess.identifier<<", the new coordinator"<<endl;    
        }
    }

    return 0;
}