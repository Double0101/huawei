#ifndef YUXIAO_H
#define YUXIAO_H
class machine{
        public:

                int fcpu[15];
                int fmem[15];
                int cpu;
                int mem;
                map<int,int> fdict;
                machine(int cpu,int mem){
                        this->cpu = cpu;
                        this->mem = mem;
                        int xcpu[15] = {1,1,1,2,2,2,4,4,4 ,8,8 ,8 ,16,16,16};
                        int xmem[15] = {1,2,4,2,4,8,4,8,16,8,16,32,16,32,64};
                        for (int i = 0; i < 15; i++) {
                                fcpu[i] = xcpu[i];
                                fmem[i] = xmem[i];
                        }

                }

                void update_machine(int findex){
                        this->cpu = this->cpu - fcpu[findex];
                        this->mem = this->mem - fmem[findex];
                        if(fdict.find(findex)!=fdict.end()){
                                this->fdict[findex] += 1;
                        } else{
                                this->fdict[findex] = 1;
                        }
                }
};

class machineGroup{
        public:
                vector<machine> machinelist;

                void add_machine(machine new_machine){
                        this->machinelist.push_back(new_machine);
                }
                void change_machine(int index,int findex){
                        this->machinelist[index].update_machine(findex);
                }
};
#endif
