#! /bin/bash

  CMD="export"
  SEP="="

# test if export is supported
export 1>/dev/null 2>/dev/null
if [ "${?}" == 0 ]; then
  CMD="export"
  SEP="="
else
  setenv 1>/dev/null 2>/dev/null
  if [ "${?} == 0" ]; then
  CMD="setenv"
  SEP=" "
  else
  echo "Neither setenv nor export found!"
  fi
fi 

#-Find script path
if [ -n "$ZSH_VERSION" ]; then
   SCRIPTPATH="$( cd "$(dirname $(dirname "${(%):-%x}"))" && pwd )"
elif [ -n "$tcsh" ]; then
   SCRIPTPATH="$( cd "$(dirname $(dirname "$0"))" && pwd )"
elif [ -n "$BASH_VERSION" ]; then
   SCRIPTPATH="$( cd "$(dirname $(dirname "${BASH_SOURCE[0]}"))" && pwd )"
else
   echo "neither bash or zsh is used, abort"
   exit 1
fi

# export environment variable
${CMD} NIMPROOTWORKDIR${SEP}$SCRIPTPATH
${CMD} NIMPANADIR${SEP}$NIMPROOTWORKDIR/nimpAnaLib
${CMD} NIMPSIMDIR${SEP}$NIMPROOTWORKDIR/nimpSim
${CMD} TPCWORKDIR${SEP}$NIMPANADIR/reconst/nimpTPC
${CMD} MATEROOTDIR${SEP}$SCRIPTPATH
${CMD} MATESIMDIR${SEP}$SCRIPTPATH/mateSim
${CMD} MATEANADIR${SEP}$MATEROOTDIR/mateRootAnaLib

NPARCH=$(uname)
# mac os x case
if [ "${NPARCH}" = "Darwin" ] ; 
then
  ${CMD} DYLD_LIBRARY_PATH${SEP}$MATESIMDIR/lib:$DYLD_LIBRARY_PATH
else 
  ${CMD} LD_LIBRARY_PATH${SEP}$MATESIMDIR/lib:$LD_LIBRARY_PATH
  ${CMD} LD_LIBRARY_PATH${SEP}$NIMPSIMDIR/lib:$LD_LIBRARY_PATH
fi

${CMD} PATH=$MATESIMDIR/bin:$PATH
${CMD} PATH=$NIMPSIMDIR/bin:$PATH

