##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=OSPhase1
ConfigurationName      :=Debug
WorkspacePath          :=C:/Users/gkigu/OneDrive/Documents/codelite_C++_projects
ProjectPath            :="C:/Users/gkigu/OneDrive/Documents/codelite_C++_projects/OSProject backup"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=gkigu
Date                   :=29/10/2016
CodeLitePath           :="C:/Program Files/CodeLite"
LinkerName             :=C:/TDM-GCC-64/bin/g++.exe
SharedObjectLinkerName :=C:/TDM-GCC-64/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="OSPhase1.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=C:/TDM-GCC-64/bin/windres.exe
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/TDM-GCC-64/bin/ar.exe rcu
CXX      := C:/TDM-GCC-64/bin/g++.exe
CC       := C:/TDM-GCC-64/bin/gcc.exe
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := C:/TDM-GCC-64/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/Disk.cpp$(ObjectSuffix) $(IntermediateDirectory)/PCB.cpp$(ObjectSuffix) $(IntermediateDirectory)/Loader.cpp$(ObjectSuffix) $(IntermediateDirectory)/RAM.cpp$(ObjectSuffix) $(IntermediateDirectory)/Scheduler.cpp$(ObjectSuffix) $(IntermediateDirectory)/Dispatcher.cpp$(ObjectSuffix) $(IntermediateDirectory)/CPU.cpp$(ObjectSuffix) $(IntermediateDirectory)/Metrics.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@$(MakeDirCommand) "./Debug"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/gkigu/OneDrive/Documents/codelite_C++_projects/OSProject backup/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix)main.cpp

$(IntermediateDirectory)/Disk.cpp$(ObjectSuffix): Disk.cpp $(IntermediateDirectory)/Disk.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/gkigu/OneDrive/Documents/codelite_C++_projects/OSProject backup/Disk.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Disk.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Disk.cpp$(DependSuffix): Disk.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Disk.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Disk.cpp$(DependSuffix) -MM Disk.cpp

$(IntermediateDirectory)/Disk.cpp$(PreprocessSuffix): Disk.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Disk.cpp$(PreprocessSuffix)Disk.cpp

$(IntermediateDirectory)/PCB.cpp$(ObjectSuffix): PCB.cpp $(IntermediateDirectory)/PCB.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/gkigu/OneDrive/Documents/codelite_C++_projects/OSProject backup/PCB.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/PCB.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PCB.cpp$(DependSuffix): PCB.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/PCB.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/PCB.cpp$(DependSuffix) -MM PCB.cpp

$(IntermediateDirectory)/PCB.cpp$(PreprocessSuffix): PCB.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PCB.cpp$(PreprocessSuffix)PCB.cpp

$(IntermediateDirectory)/Loader.cpp$(ObjectSuffix): Loader.cpp $(IntermediateDirectory)/Loader.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/gkigu/OneDrive/Documents/codelite_C++_projects/OSProject backup/Loader.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Loader.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Loader.cpp$(DependSuffix): Loader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Loader.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Loader.cpp$(DependSuffix) -MM Loader.cpp

$(IntermediateDirectory)/Loader.cpp$(PreprocessSuffix): Loader.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Loader.cpp$(PreprocessSuffix)Loader.cpp

$(IntermediateDirectory)/RAM.cpp$(ObjectSuffix): RAM.cpp $(IntermediateDirectory)/RAM.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/gkigu/OneDrive/Documents/codelite_C++_projects/OSProject backup/RAM.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/RAM.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/RAM.cpp$(DependSuffix): RAM.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/RAM.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/RAM.cpp$(DependSuffix) -MM RAM.cpp

$(IntermediateDirectory)/RAM.cpp$(PreprocessSuffix): RAM.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/RAM.cpp$(PreprocessSuffix)RAM.cpp

$(IntermediateDirectory)/Scheduler.cpp$(ObjectSuffix): Scheduler.cpp $(IntermediateDirectory)/Scheduler.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/gkigu/OneDrive/Documents/codelite_C++_projects/OSProject backup/Scheduler.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Scheduler.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Scheduler.cpp$(DependSuffix): Scheduler.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Scheduler.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Scheduler.cpp$(DependSuffix) -MM Scheduler.cpp

$(IntermediateDirectory)/Scheduler.cpp$(PreprocessSuffix): Scheduler.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Scheduler.cpp$(PreprocessSuffix)Scheduler.cpp

$(IntermediateDirectory)/Dispatcher.cpp$(ObjectSuffix): Dispatcher.cpp $(IntermediateDirectory)/Dispatcher.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/gkigu/OneDrive/Documents/codelite_C++_projects/OSProject backup/Dispatcher.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Dispatcher.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Dispatcher.cpp$(DependSuffix): Dispatcher.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Dispatcher.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Dispatcher.cpp$(DependSuffix) -MM Dispatcher.cpp

$(IntermediateDirectory)/Dispatcher.cpp$(PreprocessSuffix): Dispatcher.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Dispatcher.cpp$(PreprocessSuffix)Dispatcher.cpp

$(IntermediateDirectory)/CPU.cpp$(ObjectSuffix): CPU.cpp $(IntermediateDirectory)/CPU.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/gkigu/OneDrive/Documents/codelite_C++_projects/OSProject backup/CPU.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CPU.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CPU.cpp$(DependSuffix): CPU.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CPU.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/CPU.cpp$(DependSuffix) -MM CPU.cpp

$(IntermediateDirectory)/CPU.cpp$(PreprocessSuffix): CPU.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CPU.cpp$(PreprocessSuffix)CPU.cpp

$(IntermediateDirectory)/Metrics.cpp$(ObjectSuffix): Metrics.cpp $(IntermediateDirectory)/Metrics.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/gkigu/OneDrive/Documents/codelite_C++_projects/OSProject backup/Metrics.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Metrics.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Metrics.cpp$(DependSuffix): Metrics.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Metrics.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Metrics.cpp$(DependSuffix) -MM Metrics.cpp

$(IntermediateDirectory)/Metrics.cpp$(PreprocessSuffix): Metrics.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Metrics.cpp$(PreprocessSuffix)Metrics.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


