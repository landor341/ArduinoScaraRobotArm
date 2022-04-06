/*
  GCodeInterpreter.cpp - Class for interpreting serial inputs into GCodeCommands for use with arduino based cnc.
  Created by Landon R. Faris, June 2, 2021.
*/


#include "Arduino.h"
#include "GCodeInterpreter.h"

GCodeInterpreter::GCodeInterpreter(int bufferLength=100)
:bufferLength(bufferLength), commandBuffer{new GCodeCommand[bufferLength]{ GCodeCommand() }} {}

int GCodeInterpreter::getBufferLength() { return bufferLength; }

boolean GCodeInterpreter::interpretCommandString(String str) {
    String command = str;
    
    uint8_t codeNum = NULL;
    char codeType;
    GCodeCommandField commandParameters[7] = {GCodeCommandField()};
    uint8_t currentParameter = 0;

    String word = "";
    if (!getNextWord(&command, &word)) return false;
    if (!isAlpha(word[0])) return false; //Checks that first letter is an alphabetical letter
    codeType = word[0];
    codeNum = word.substring(1).toInt();


    while (getNextWord(&command, &word)) {
        commandParameters[currentParameter] = GCodeCommandField(word[0], word.substring(1).toInt());
        currentParameter++;
    }
    
    addCommand(GCodeCommand(codeType, codeNum, commandParameters));
    return true;
}

boolean GCodeInterpreter::getNextWord(String *str, String *word) { //if the string is all spaces this will fail
    int stringLength = sizeof(str)/sizeof(str[0]);
    int i=0;
    int firstLetterIndex;
    int lastLetterIndex;

    for (void; i<stringLength; i++) {
        if ((*str)[i] != ' ') {
            firstLetterIndex = i;
            break; //make sure not to include any beginning spaces
        }
    }

    for (void; i<stringLength; i++) {
        if ((*str)[i] == ' ') {
            break; //i now becomes the location of the end of the word
        }
    }
    lastLetterIndex = i;

    if (firstLetterIndex == lastLetterIndex) { //the string was either empty or all spaces
        *word = " ";
        *str = " ";
        return false;
    }

    *word = (*str).substring(firstLetterIndex, lastLetterIndex);
    *str = (*str).substring(lastLetterIndex, stringLength-1);
    return true;
}

boolean GCodeInterpreter::addCommand(GCodeCommand command) {
    if (numberOfCommands < bufferLength) {
        incrementBufferArray();
        commandBuffer[0] = command;
    }
}

GCodeCommand GCodeInterpreter::getNextCommand() {
    GCodeCommand nextCommand = commandBuffer[numberOfCommands-1];
    commandBuffer[numberOfCommands-1] = GCodeCommand();
    return nextCommand;
}

void GCodeInterpreter::emptyBuffer() {for (int i=99; i>99-numberOfCommands; i--) { commandBuffer[i] = GCodeCommand(); }}

void GCodeInterpreter::incrementBufferArray() {
    for (int i=numberOfCommands; i>0; i++) {
        commandBuffer[i] = commandBuffer[i-1];
    }
    numberOfCommands++;
}

// unsigned int numberOfCommands = 0;
// GCodeCommand commandBuffer[100]{ GCodeCommand() };