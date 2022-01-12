#include <bits/stdc++.h>
using namespace std;

ifstream fin;
ofstream fout;
int SI,PI,TI;

bool occupied_pages[30];

int IOI;
int UC = 0; // universal counter
int ch[4]={0,5,5,2};

class PCB {
private:
	int TLL,TTL,LLC,TLC,page_table_ptr,terminate_code,TS, TSC;
	string p_id;

public:
	void initialize_PCB(string limits)
	{
		//initialize the contents of PCB
		cout<<"Initializing PCB\n";
        p_id=limits.substr(0,4);
		TTL=s_to_i(limits.substr(4,2))*100+s_to_i(limits.substr(6,2));
		TLL=s_to_i(limits.substr(8,2))*100+s_to_i(limits.substr(10,2));
		LLC=0;
        TLC=0;
        terminate_code=0;
        TSC = TTL;
        TS = 0;
	}
	int s_to_i(string operand)//ok
	{
		//return the integer no for the given string
		if(operand[0]>='0' && operand[0]<='9' && operand[1]>='0' && operand[1]<='9')
			return ((int)operand[0]-48)*10+((int)operand[1]-48);
		return -1;
	}
	int get_page_table_ptr()
	{
		//reterieve page table pointer
        cout<<"PTR: "<<page_table_ptr<<endl;
        fout<<"PTR: "<<page_table_ptr<<endl;
		return page_table_ptr;
	}
	int set_page_table_ptr(int ptr)
	{
		//set the page table pointer
		page_table_ptr=ptr;
        return page_table_ptr;
	}
	void increment_TLC()
	{
		TLC++;
	}
	void increment_LLC()
	{
		LLC++;
	}
	int get_TLC()
	{
		return TLC;
	}
	string get_pid()
	{
		return p_id;
	}

	int get_terminate_code()
	{
		return terminate_code;
	}

	void set_terminate_code(int t_c)
	{
		terminate_code=t_c;
	}

	int get_LLC()
	{
		return LLC;
	}

	int TLC_is_greater_than_TTL()
	{
		//compare TLC anf TTL
		if(TLC>TTL)
			return 1;
		else
			return 0;
	}

	int LLC_is_greater_than_TLL()
	{
		//compare LLC and TLL
		if(LLC>TLL)
			return 1;
		else
			return 0;
	}
};
PCB process;


class supervisory_storage
{
	private:
		queue < string > ibq,obq;
		int ebc,ibc,obc;
	public:
		supervisory_storage()
		{
			ebc=10;
            cout<<"Empty Buffers: "<<ebc<<endl;
            fout<<"Empty Buffers: "<<ebc<<endl;

		}
		void inc_ebc()
		{
			ebc++;
		}
		void dec_ebc()
		{
			ebc--;

		}
		int get_ebc()
		{
            cout<<"Empty Buffers: "<<ebc<<endl;
            fout<<"Empty Buffers: "<<ebc<<endl;

			return ebc;
		}
		void fill_ibq(string temp)
		{
            cout<<"\nFilling IBQ\n";
			fout<<"\nFilling IBQ\n";

            ibq.push(temp);
		}
		string get_cards_from_ib()
		{
            cout<<"\nGetting cards from IB\n";
			fout<<"\nGetting cards from IB\n";

            string s=ibq.front();
			ibq.pop();
			return s;
		}

        void fill_obq(string temp) {
            cout<<"\nFilling OBQ\n";
			fout<<"\nFilling OBQ\n";

            ibq.push(temp);
        }

        string get_cards_from_ob()
		{
            cout<<"\nGetting cards from OB\n";
			fout<<"\nGetting cards from OB\n";

             string s;
            // if(!obq.empty())
             s=obq.front();
			ibq.pop();
			return s;
		}

}super;

class aux_drum
{
	private:
		string drum[100];
		int curr;
	public:
		aux_drum()
		{
			curr=0;
            cout<<"Current track: "<<curr<<endl;
            fout<<"Current track: "<<curr<<endl;

		}
		void set_drum(string s)
		{
			drum[curr]=s;
			++curr;
		}
		string get_drum_entry(int i)
		{
			return drum[i];
		}
		int get_curr()
		{
            cout<<"Current track: "<<curr<<endl;
			fout<<"Current track: "<<curr<<endl;

            return curr;
		}
}drum_obj;

void increment_IOI(int channel){
    switch(channel) {
        case 1:
        IOI += 1;
        break;
        case 2:
        IOI += 2;
        case 3:
        IOI += 4;
    }
}

void simulation() {

    cout<<"\nIN SIMULATION\n";
    fout<<"\nIN SIMULATION\n";


    if(process.TLC_is_greater_than_TTL())
		TI=2;

    //if(process.getTSC() == process.getTS())
      //  TI = 1;


	for(int i=0;i<3;i++)
	{
		if(ch[i]!=0)
			ch[i]--;
		else
		{
			switch(i+1) {
        case 1:
        IOI += 1;
        break;
        case 2:
        IOI += 2;
        case 3:
        IOI += 4;
    }
		}
	}
    cout<<"IOI : "<<IOI<<endl<<endl;
    fout<<"IOI : "<<IOI<<endl<<endl;

}

class memory
{
	private:
		char mem[300][4];
		char ch;
		int page_table_ptr;

	public:
		void reset()//ok
		{
			//reset the memory by replacing every symbol in 2D array by $
			memset(mem,'$',sizeof(char)*300*4);
			memset(occupied_pages,false,sizeof(bool)*30);
			page_table_ptr=process.get_page_table_ptr();
			page_table_ptr=rand()%30;

            // cout<<"PTR: "<<page_table_ptr<<endl;

			occupied_pages[page_table_ptr]=true;
			page_table_ptr*=10;
            //  cout<<"PTR: "<<page_table_ptr<<endl;
			process.set_page_table_ptr(page_table_ptr);
			SI=PI=TI=0;
		}
		string get_mem(int pos)//get word form memory
		{
			//get the memory contents of given position
			string temp="";
			for(int i=0;i<4;i++)
				temp+=mem[pos][i];
			return temp;
		}
		void set_mem(string s, int pos)//store word in mem
		{
			//set the memory for the recieved value at postion
			for(int i=0;i<4;i++)
				mem[pos][i]=s[i];
		}
		void set_page_table(int row_num,int page_no)
		{
			//set page table
			page_table_ptr=process.get_page_table_ptr();
            // cout<<"PTR: "<<page_table_ptr<<endl;
			ostringstream temp;
			temp << page_no;
			string table_entry;
            // cout<<"page_no: "<<page_no<<endl;
			if(page_no<10)
				table_entry="$10"+temp.str();
			else
				table_entry="$1"+temp.str();
			set_mem(table_entry,page_table_ptr+row_num);
		}
		int allocate_page()
		{
			//allocate page logic goes here
			int page_no=rand()%30;
			while(occupied_pages[page_no]==true)
				page_no=rand()%30;
			occupied_pages[page_no]=true;
            cout<<"page_no: "<<page_no<<endl;
            fout<<"page_no: "<<page_no<<endl;

			return page_no;
		}

		void store_card(string s,int mem_cnt)
		{
			//extract the words and call the setmem function
			string word="";
			int page_no=allocate_page();
			set_page_table(mem_cnt, page_no);
			page_no*=10;
			for(int i=0;i<s.length();i+=4)
			{
				for(int j=0;j<4;j++)
				{
					word+=s[i+j];
				}
				set_mem(word,page_no);
				page_no++;
				word="";
			}
		}
		void print_mem()
		{
			// int flag=0;
			for(int i=0;i<300;i++)
			{

				cout<<"["<<i<<"] : ";
                fout<<"["<<i<<"] : ";

				for(int j=0;j<4;j++)
				{
					cout<<mem[i][j];
                    fout<<mem[i][j];

                }
				cout<<endl;
                fout<<endl;

			}
		}
}m_obj;

class cpu
{
	private:
		int fetched_IC,pos,flag,program_card_cnt;
		bool terminate,fetched_C;
		string fetched_IR,operand,opreator,fetched_R,compare_string;
		char IR[4],R[4],IC[2];
		bool C,run_mos;
		string s;

	public:
	//set and reset function of all the register
		int s_to_i(string operand)//ok
		{
			//return the integer no for the given string
			if(operand[0]>='0' && operand[0]<='9' && operand[1]>='0' && operand[1]<='9')
				return ((int)operand[0]-48)*10+((int)operand[1]-48);
			return -1;
		}
		void set_IC()
		{
			IC[0]='0';
			IC[1]='0';
		}
		void set_IC(int pos)//ok
		{
			IC[1]=((char)pos%10)+48;
			pos=pos/10;
			IC[0]=((char)pos%10)+48;
		}
		int get_IC()
		{
			int val;
			val=((int)IC[0]-48)*10+((int)IC[1]-48);
			return val;
		}
		void inc_IC()//ok
		{
			int val;
			val=get_IC();
			val++;
			set_IC(val);
		}

		void set_IR(int IC)//ok
		{
            // getting data for execution
			string returned_value="";
			returned_value=m_obj.get_mem(IC);
			for(int i=0;i<4;i++)
			IR[i]=returned_value[i];
		}
		string get_IR()//ok
		{
			string ret_IR="";
			for(int i=0;i<4;i++)
			ret_IR+=IR[i];
			return ret_IR;
		}
		void set_R(int pos)//ok
		{
            // getting data for execution
			string returned_value="";
			returned_value=m_obj.get_mem(pos);
			for(int i=0;i<4;i++)
				R[i]=returned_value[i];
		}
		string get_R()//ok
		{
			string ret_R="";
			for(int i=0;i<4;i++)
			{
				ret_R+=R[i];
			}
            cout<<"R: "<<R<<endl;
            fout<<"R: "<<R<<endl;

			return ret_R;
		}
		void set_C(bool value)//ok
		{
			C=value;
		}
		bool get_C()//ok
		{
			return C;
		}

        int address_tranlation(int virtual_add)
		{
			//address translation logic
			int page=process.get_page_table_ptr()+(virtual_add/10);//get the page table pointer and the virtual address tens place
			string value_page=m_obj.get_mem(page);//get the required page from the memory
			if(value_page[1]=='$')//check for the page fault
			{
				PI=3;
				return -1;
			}
			value_page=value_page.substr(2,2);//reterieve the page value
			return (s_to_i(value_page)*10+(virtual_add%10));//return the real by adding the unit place to retrieve the specific instruction in the that page
		}
		int address_tranlation(string op)
		{
			//check for operan error
			if(s_to_i(op)==-1)
			{
				PI=2;
				return -2;
			}
			else
				address_tranlation(s_to_i(op));//no operand error go for translation logic
		}

        void IR1()
		{
			if(fin.eof())
				flag=4;
			else
			{
				getline(fin,s);

                cout<<"IN CH1....reading data from card reader\nRead value : "<<s<<endl<<endl;

                fout<<"IN CH1....reading data from card reader\nRead value : "<<s<<endl<<endl;


            	if(s.find("$AMJ")!=-1)
				{
					//reset the memory
					process.initialize_PCB(s.substr(4,12));
					flag=1;
					program_card_cnt=0;
				}
				else if(s.find("$DTA")!=-1)
				{
					flag=2;
				}
				else if(s.find("$END")!=-1)
				{
					//proceed to the next job
					flag=3;
				}
				else if(flag==1 || flag==2)
				{
					//load the program card as soon as it comes
					cout<<"Pushing data in IBQ"<<endl;
                    fout<<"Pushing data in IBQ"<<endl;

                    super.fill_ibq(s);
					super.dec_ebc();
				}
				ch[1]=5;
                UC += 5;
			}
			cout<<"--------------------------------------------------"<<endl;
            cout<<"UC : "<<UC<<endl;
            fout<<"UC : "<<UC<<endl;

		}

        void IR2()
        {
            cout<<"IN CH2\n";
            fout<<"IN CH2\n";

            // cout<<"curr pos: "<<program_card_cnt<<endl;
// int pos = 0;

             string temp = m_obj.get_mem(program_card_cnt);
             super.dec_ebc();
            drum_obj.set_drum(temp);
            process.increment_TLC();

            if(process.TLC_is_greater_than_TTL()) {
                process.set_terminate_code(3);
            } else {
                int curr_drum = drum_obj.get_curr();
                super.get_ebc();
                string temp = drum_obj.get_drum_entry(curr_drum);
            fout<<temp;
            }


            string temp2 = super.get_cards_from_ob();
            super.inc_ebc();

            ch[2] = 5;
            UC += 5;

            cout<<"--------------------------------------------------"<<endl;
            cout<<"UC : "<<UC<<endl;
            fout<<"UC : "<<UC<<endl;

            return;
        }

        void IR3()
		{
            cout<<"IN CH3\n";
            fout<<"IN CH3\n";

			string temp;
			if(flag==4)
			{
                cout<<"EOF found...Memory printing\n\n";
                fout<<"EOF found...Memory printing\n\n";

				m_obj.print_mem();
				// exit(0);
                IR2();
            return;

			}
			if(super.get_ebc()!=10)
			{
				temp=super.get_cards_from_ib();
				cout<<"Found data in IFQ....Data is "<<temp<<endl<<endl;
                fout<<"Found data in IFQ....Data is "<<temp<<endl<<endl;

                super.inc_ebc();
				drum_obj.set_drum(temp);
				if(flag==1)
					program_card_cnt++;
			}
			else if(flag==3)
			{

				cout<<"Moving from drum to main memory\n";
                fout<<"Moving from drum to main memory\n";

                for(int i=0;i<program_card_cnt;i++)
				{
					s=drum_obj.get_drum_entry(i);
					m_obj.store_card(s,i);          // storing data in main memory
				}
				// program_card_cnt=0;
			}
            // else {
            //      int curr_drum = drum_obj.get_curr();
            // string temp = drum_obj.get_drum_entry(curr_drum);
            // super.fill_obq(temp);
            // super.dec_ebc();


            // }
			ch[3]=2;
            UC += 2;
            cout<<"--------------------------------------------------"<<endl;
            cout<<"UC : "<<UC<<endl;
            fout<<"UC : "<<UC<<endl;

		}

         void WT(int pos) {
            // string temp = m_obj.get_mem(pos);
            // drum_obj.set_drum(temp);
            // process.increment_TLC();

            // if(process.TLC_is_greater_than_TTL()) {
            //     process.set_terminate_code(3);
            // } else {
            //     int curr_drum = drum_obj.get_curr();
            //     super.get_ebc();
            //     string temp = drum_obj.get_drum_entry(curr_drum);
            // }
        }

        void startexe()
		{
			//fetch decode execute cycle given below
			set_IC(0);
			terminate=false;
			while(!terminate)
			{
                UC++;

				//fetch ic
				//fetch ir form the location specified by ic
				//get the value of operator and operand

				run_mos=false;
				fetched_IC=address_tranlation(get_IC());
				inc_IC();
				set_IR(fetched_IC);
				fetched_IR=get_IR();

				opreator=fetched_IR.substr(0,2);
				operand=fetched_IR.substr(2,2);
				pos=address_tranlation(s_to_i(operand));
				if(address_tranlation(operand)!=-2)
				{
					if(!(opreator.compare("LR")))//ok
					{
						//set the contents of the register R from the given location of memory specified in the operand

						if(pos==-1)
						{
							run_mos=true;//if operand error runmos = true
						}
						else
						{
							set_R(pos);
							process.increment_TLC();

						}
					}
					else if (!(opreator.compare("SR")))//ok
					{
						//get the contents of register R
						//store them at the location of memory specified in the operand
						//cout<<"SR";

						fetched_R=get_R();
						if(pos==-1)
						{
							run_mos=true;
						}
						else
						{
							m_obj.set_mem(fetched_R, pos);
							process.increment_TLC();
						}
					}
					else if (!(opreator.compare("CR")))//ok
					{
						//get the contents of register r
						//compare with given memory location
						//if the values of above two matches then set toggle register to true
						//else set the toggle register to false
						//cout<<"CR";
						fetched_R=get_R();
						if(pos==-1)
						{
							run_mos=true;
						}
						else
						{
							process.increment_TLC();
							compare_string=m_obj.get_mem(pos);
							if(fetched_R.compare(compare_string)==0)
								set_C(true);
							else
								set_C(false);
						}
					}
					else if (!(opreator.compare("BT")))//ok
					{

						//if the value of toggle register is true
						//we change the value of ic
						//cout<<"BT";
						//fetched_C=get_C();
						if(fetched_C)
						{
							fetched_C=get_C();
							//int get_physical_add=address_tranlation();
							set_IC(s_to_i(operand));
						}
						process.increment_TLC();
					}
					else if (!(opreator.compare("GD")))//ok
					{
						if(pos!=-1)
						{
							process.increment_TLC();
							SI=1;
						}
						run_mos=true;
					}
					else if (!(opreator.compare("PD")))//ok
					{
						if(pos!=-1)
						{
							process.increment_TLC();
							SI=2;
						}
						run_mos=true;
					}
					else if (!(opreator.compare("H")))//ok
					{
						process.increment_TLC();
						fetched_IR="H";
						SI=3;
						run_mos=true;
					}
					else
					{
						PI=1;
						run_mos=true;
					}
				}
				else
				{
					run_mos=true;
				}
				if(process.TLC_is_greater_than_TTL())
				{
					TI=2;
					run_mos=true;
					terminate=true;
					process.set_terminate_code(3);
				}
				if(run_mos)
					MOS();
			}
			cout<<"--------------------------------------------------"<<endl;
            cout<<"UC : "<<UC<<endl;
            fout<<"UC : "<<UC<<endl;

		}

		void MOS()
		{
			//acording to ti si and pi set here we will handle the interrupt
			if(TI==0 && SI==1)
			{
				//get the instrution of the file in terms of 4 words
				//store it one by one into memory
				//at start store the program card from memory location with unit place 0

				string s;
				pos=(pos/10)*10;
				getline(fin,s);
				if(s.find("$END")!=-1)// if the $END encountered before hand then out of data
				{
					terminate=true;
					process.set_terminate_code(1);
				}
				else
				{
					if(!s.empty() && s[s.size()-1]=='\r')
						s.erase(s.size()-1);
					int len=s.length(),start=0,i;
					string s1;
					for(i=pos;start<len;i++)
					{
						if((len-start)<4)
							s1=s.substr(start,(len-start));
						else
							s1=s.substr(start,4);
						start+=4;
						m_obj.set_mem(s1,i);
					}
				}
				SI=0;
			}
			else if(TI==2 && SI==1)
			{
				terminate=true;
				process.set_terminate_code(3);
			}
			else if((TI==0 || TI==2) && SI==2)
			{
				process.increment_LLC();
				if(process.LLC_is_greater_than_TLL())//lime limit exceeded
				{
					terminate=true;
					process.set_terminate_code(2);
				}
				//put the data from memory into the file specified
				else
				{
					int pos=address_tranlation(s_to_i(operand)),flag=0;
					pos=(pos/10)*10;
					string ans="",temp="";
					for(int i=pos;i<pos+10;i++)
					{
						temp=m_obj.get_mem(i);
						for(int j=0;j<4;j++)
						{
							if(temp[j]=='\0' || temp[j]=='$')
							{
								break;
								flag=1;
							}
							ans+=temp[j];
						}
						if(flag)
							break;
					}
					fout<<ans<<endl;
					if(TI==2)//time limit exceeded
					{
						terminate=true;
						process.set_terminate_code(3);
					}
				}
				SI=0;
			}
			else if((TI==0 || TI==2) && SI==3)//no error has ocurred terminated the program normally
			{
				//make terminate true to end the program
				//as we encountered the halt instruction

				terminate=true;
				process.set_terminate_code(0);
			}
			else if(TI==0 && PI==1)//operation code error has occured
			{
				process.set_terminate_code(4);
				terminate=true;
			}
			else if(TI==0 && PI==2)//operand code error has ocurred
			{
				process.set_terminate_code(5);
				terminate=true;
			}

			else if(TI==0 && PI==3)//handle the valid page fault or terminate with invaild page faults
			{
				if(!(opreator.compare("GD")) || !(opreator.compare("SR")))
				{
					process.increment_TLC();
					int page_no=m_obj.allocate_page();
					m_obj.set_page_table((s_to_i(operand))/10,page_no);
					set_IC(get_IC()-1);
				}
				else
				{
					process.set_terminate_code(6);
					terminate=true;
				}
			}

			else if(TI==2 && PI==1)//time limit exceeded with operation code error
			{
				process.set_terminate_code(7);
				terminate=true;
			}

			else if(TI==2 && PI==2)//time limit exceeded with operand error
			{
				process.set_terminate_code(8);
				terminate=true;
			}

			else if(TI==2 && PI==3)//time limit exceeded
			{
				process.set_terminate_code(3);
				terminate=true;
			}
				switch(IOI)
			{
				case 0:
				break;
				case 1:
					IR1();
				break;
				case 2:
                IR2();
                IR2();
				break;
				case 3:
                IR2();
					IR1();

				break;
				case 4:
					IR3();
				break;
				case 5:
					IR3();
					IR1();
				break;
				case 6:
					IR3();
                    IR2();
				break;
				case 7:
					IR3();
                    IR2();
					IR1();

				break;
			}
			IOI=0;
			if(terminate)
			{
				fout<<process.get_pid()<<" ";
				switch(process.get_terminate_code())
				{
					case 0:fout<<"NO ERROR\n";
					       break;
					case 1:fout<<"OUT OF DATA\n";
					       break;
					case 2:fout<<"LINE LIMIT EXCEEDED\n";
					       break;
					case 3:fout<<"TIME LIMIT EXCEEDED\n";
					       break;
					case 4:fout<<"OPERATION CODE ERROR\n";
					       break;
					case 5:fout<<"OPERAND ERROR\n";
					       break;
					case 6:fout<<"INVALID PAGE FAULT\n";
					       break;
					case 7:fout<<"TIME LIMIT EXCEEDED with OPERATION CODE ERROR\n";
					       break;
					case 8:fout<<"TIME LIMIT EXCEEDED with OPERAND ERROR\n";
					       break;
				}
				fout<<get_IC()<<" "<<fetched_IR<<" "<<process.get_TLC()<<" "<<process.get_LLC()<<endl;
				fout<<endl<<endl;
			}
		}
}exe;

int main() {
  fin.open("input.txt");
	fout.open("output.txt");
	string s,s1;
	int mem_cnt=0;
    cout<<"Universal counter initialized:"<<endl<<endl;
    cout<<"--------------------------------------------------"<<endl;
    cout<<"UC: "<<UC<<endl<<endl;
    fout<<"Universal counter initialized:"<<endl<<endl;
    fout<<"UC: "<<UC<<endl<<endl;

	m_obj.reset();
	while(true)
	{
		simulation();
		exe.MOS();

	}
    cout<<"\nUC: "<<UC<<endl;
fin.close();
	fout.close();
	return 0;
}
