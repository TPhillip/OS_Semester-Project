class Dispatcher{

  /*The dispatcher class only needs to send a the memory address of the first instruction for a process. 
  It will also update the CPU's program counter variablein the PCB if there is an interuot and the process is stoped.
  */
  
  //Needed Methods
  
  private:
  
  //We need a method that will go into the ready queue and grab a process(Im assuming the First).
  //*node get_next_process()
  {
    //we need to know how the Ready Queue is implemented before writing this method
    //assuming that the ready queue is a Stack, we can use this code:
    
    /*
    peek_on_ready_queue() ;
        ^This call will look at the top field in the queue to get the pointer, and then use that pointer to know what to add to the cpu   
    */
  }
  
  //once we have the location, we can send it to the CPU class, but we need to keep trasck of whether or not it sent correctly
  //AND we need to track to see if the original processon the CPU was finished
  void send_to_CPU(/* *node new_current_process */)
  {
    //first thing to do is check if the CPU finished its first process
    /*if( ! CPU_is_Finished())
        {
          //record the program counter and update it to the PCB
          update_PCB(CPU.get_PC_value(), current_process_node);
        }
       
    //now that we know the cpu is ready to go, we use the new location to set the registers of the cpu.
    
    set_register( 0 , new_current_process-> next instruction_instruction());
    //the set register method updates the registers,  The first parameter indicates which register to update logicly, the second parametere is the instruction 
    
    
    */
    
  }
  
};
