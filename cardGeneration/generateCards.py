#! /usr/bin/env python

import re, sys, os, time
#import subprocess as sp
from optparse import OptionParser
#Documentation: http://docs.python.org/2/howto/urllib2.html
import urllib2
import ast

def ParseInput(ArgsIn):
   '''Generate new Card classes from the online mtg API.'''
   UseMsg='''%prog [options] name
   DES 20131202.'''

   parser=OptionParser(usage=UseMsg)
#   parser.add_option('-s','--save',dest='save',action="store_true",help='Do not wipe the resultant job\'s scratch directory.')
#   parser.add_option('-F','--final',dest='final',type='float',default=2.0,help='Specify the ending distance for the curve. Default: 2.0')
   parser.add_option('-n','--cardnum',dest='cardnum',type='int',default=0,help='Set the initial index for the starting card for IdToCardIndex. Default: 0')
   parser.add_option('-f','--file',dest='file',type='str',default=None,help='Read inputs from file rather than command line')
   parser.add_option('-v','--verbose',dest='verbose',action="store_true",help='Print out more information')
   options,args=parser.parse_args(ArgsIn)
#   if len(args)<2:
#      print "file must be specified."
#      parser.print_help()
#      sys.exit(1)
#   else:
#      return options,args
   return options,args

options,args=ParseInput(sys.argv)

def is_int(s):
    try:
        int(s)
        return True
    except ValueError:
        return False

cardNames = []
if options.file:
   if os.path.exists(options.file):
      cardNameFile = open(options.file, 'r')
   else:
      print "File "+options.file+" doesn't exist!"
      sys.exit(1)
   for line in cardNameFile:
      cardNames.append(line.replace('\n', ''))
elif len(args)<2:
   print "name must be specified"
   parser.print_help()
   sys.exit(1)
else:
   args.pop(0)
   for name in args:
      cardNames.append(name)

if options.verbose:
   print cardNames

includes = []
selectCases = []
nameToIndex = []
enumList = []

for cardName in cardNames:
   url='http://mtgapi.com/api/v1/fetch/search/'+cardName+'?token=e061d09e370f286978175c04464901d162f7ec3c'
   req = urllib2.Request(url, headers={'User-Agent' : "Magic Browser"})
   response = urllib2.urlopen(req)
   the_page = response.read()
#   the_page = the_page[1:-1]
   cardListDict = ast.literal_eval(the_page)
   cardName = cardName.replace('%20',' ')
   for dictionary in cardListDict:
      if dictionary["name"] == cardName:
         cardDict = dictionary

   tempName = cardDict["name"].replace('\\u00c6','Ae')
   className = ''.join(e for e in tempName if e.isalnum())
   
   types = cardDict["type"][0].split()

   if options.verbose:
      print 'Writing header file ' + className+'.h'
   headerFile = open(className+'.h', 'w')
   headerFile.write('/*\n * '+className+'.h\n *\n * Autogenerated by generateCards.py\n *\tAuthor: dstuck\n*/\n')
   headerFile.write('\n')
   headerFile.write('#ifndef '+className.upper()+'_H_\n')
   headerFile.write('#define '+className.upper()+'_H_\n')
   headerFile.write('\n')
   if 'Creature' in cardDict['type'][0].split():
      headerFile.write('#include \"Card_Creature.h\"\n')
   elif 'Instant' in cardDict['type'][0].split():
      headerFile.write('#include \"Card_Instant.h\"\n')
   elif 'Land' in cardDict['type'][0].split():
      headerFile.write('#include \"Card_Land.h\"\n')
   headerFile.write('\n')
   if 'Creature' in cardDict['type'][0].split():
      headerFile.write('class '+className+': public Card_Creature {\n')
   elif 'Instant' in cardDict['type'][0].split():
      headerFile.write('class '+className+': public Card_Instant {\n')
   elif 'Land' in cardDict['type'][0].split():
      headerFile.write('class '+className+': public Card_Land {\n')
   headerFile.write('public:\n')
   headerFile.write('\t'+className+'();\n')
   headerFile.write('\tvirtual ~'+className+'();\n')
   if 'Land' in cardDict['type'][0].split():
      headerFile.write('\tstring GetImage();\n')
# Temp Land fix
      headerFile.write('\tvoid Play();\n')

   headerFile.write('};\n')
   headerFile.write('\n')
   headerFile.write('#endif /* '+className.upper()+'_H_ */\n')
   headerFile.write('\n')

#   if 'Creature' in cardDict['type'][0].split():
   if options.verbose:
      print 'Writing implementation file ' + className+'.cpp'
   cppFile = open(className+'.cpp', 'w')
   cppFile.write('/*\n * '+className+'.cpp\n *\n * Autogenerated by generateCards.py\n *\tAuthor: dstuck\n*/\n')
   cppFile.write('\n')
   cppFile.write('#include \"'+className+'.h\"\n')
   cppFile.write('\n')
   cppFile.write(className+'::'+className+'() {\n')
   cppFile.write('\tKeywordVanilla();\n')
   cppFile.write('\tid = '+cardDict['id']+';\n')
   cppFile.write('\tname = \"'+cardDict['name'].replace('\\u00c6','Ae')+'\";\n')
   if cardDict['cmc']:
      cppFile.write('\tcmc = '+cardDict['cmc']+';\n')
   else:
      cppFile.write('\tcmc = 0;\n')
   if "Creature" in cardDict['type'][0].split():
      cppFile.write('\tisCreature = true;\n')
   if "Basic" in cardDict['type'][0].split():
      cppFile.write('\tisBasic = true;\n')
   if "Legendary" in cardDict['type'][0].split():
      cppFile.write('\tisLegendary = true;\n')
   if "Land" in cardDict['type'][0].split():
      cppFile.write('\tisLand = true;\n')
   if "Enchantment" in cardDict['type'][0].split():
      cppFile.write('\tisEnchantment = true;\n')
   if "Artifact" in cardDict['type'][0].split():
      cppFile.write('\tisArtifact = true;\n')
   if "Instant" in cardDict['type'][0].split():
      cppFile.write('\tisInstant = true;\n')
   if "Sorcery" in cardDict['type'][0].split():
      cppFile.write('\tisSorcery = true;\n')
   for subtype in cardDict['type'][1].split():
      cppFile.write('\tsubtype.push_back(\"'+subtype+'\");\n')
   for text in cardDict['text']:
      if text[-1] == '.':
         if text == cardDict['name']+' can\'t be blocked.':
            cppFile.write('\tunblockable = true;\n')
         else:
            cppFile.write('\trulesText.push_back(\"'+text+'\");\n')
      else:
         text = re.sub(r'\([^)]*\)', '', text)
         for keyword in text.replace(',','').split():
            if keyword.lower() == 'double strike':
               cppFile.write('\tfirstStrike = true;\n')
               cppFile.write('\tregularStrike = true;\n')
            elif keyword.lower() == 'first strike':
               cppFile.write('\tfirstStrike = true;\n')
               cppFile.write('\tregularStrike = false;\n')
            elif keyword.lower() == 'trample':
               cppFile.write('\ttrample = true;\n')
            elif keyword.lower() == 'deathtouch':
               cppFile.write('\tdeathtouch = true;\n')
            elif keyword.lower() == 'haste':
               cppFile.write('\thaste = true;\n')
            elif keyword.lower() == 'lifelink':
               cppFile.write('\tlifelink = true;\n')
            elif keyword.lower() == 'vigilance':
               cppFile.write('\tvigilance = true;\n')
            elif keyword.lower() == 'indestructable':
               cppFile.write('\tindestructable = true;\n')
            elif keyword.lower() == 'flash':
               cppFile.write('\tflash = true;\n')
            elif keyword.lower() == 'reach':
               cppFile.write('\treach = true;\n')
            elif keyword.lower() == 'flying':
               cppFile.write('\tflying = true;\n')
            elif keyword.lower() == 'intimidate':
               cppFile.write('\tintimidate = true;\n')
#               elif keyword.lower() == 'unblockable':
#                  cppFile.write('\tunblockable = true;\n')
            elif keyword.lower() == 'hexproof':
               cppFile.write('\thexproof = true;\n')
            elif keyword.lower() == 'shroud':
               cppFile.write('\tshroud = true;\n')
            else:
               cppFile.write('\trulesText.push_back(\"'+keyword+'\");\n')
   for outerFlavor in cardDict['flavor']:
      for flavorText in outerFlavor:
         flavorText = flavorText.replace('\\u2014','--').rstrip('\n').replace('\"','\\\"').replace('\'','\\\'').rstrip()
         cppFile.write('\tflavor.push_back(\"'+flavorText+'\");\n')
   if cardDict['power']:
      cppFile.write('\tpower = '+cardDict['power']+';\n')
   else:
      cppFile.write('\tpower = 0;\n')
   if cardDict['toughness']:
      cppFile.write('\ttoughness = '+cardDict['toughness']+';\n')
   else:
      cppFile.write('\ttoughness = 0;\n')
   if cardDict['loyalty']:
      cppFile.write('\tloyalty = '+cardDict['loyalty']+';\n')
   else:
      cppFile.write('\tloyalty = 0;\n')
   cppFile.write('\tset = \"'+cardDict['set'].replace('\"','\\\"')+'\";\n')
   cppFile.write('\trarity = \"'+cardDict['rarity']+'\";\n')
   cppFile.write('\tcardNumber = '+cardDict['number']+';\n')
   cppFile.write('\timage = \"'+cardDict['image'].replace('\\/','/')+'\";\n')
   for color in cardDict['mana']:
      if is_int(color):
         cppFile.write('\tmana[colors::O]+='+color+';\n')
      elif color=='W':
         cppFile.write('\tmana[colors::W]++;\n')
         cppFile.write('\tcolor[colors::W] = true;\n')
      elif color=='U':
         cppFile.write('\tmana[colors::U]++;\n')
         cppFile.write('\tcolor[colors::U] = true;\n')
      elif color=='B':
         cppFile.write('\tmana[colors::B]++;\n')
         cppFile.write('\tcolor[colors::B] = true;\n')
      elif color=='R':
         cppFile.write('\tmana[colors::R]++;\n')
         cppFile.write('\tcolor[colors::R] = true;\n')
      elif color=='G':
         cppFile.write('\tmana[colors::G]++;\n')
         cppFile.write('\tcolor[colors::G] = true;\n')
      else:
         print color
   cppFile.write('\n')
   cppFile.write('\tDefaultInit();\n')
   cppFile.write('}\n')
   cppFile.write('\n')
   cppFile.write(className+'::~'+className+'() {\n')
   cppFile.write('}\n')
   if 'Land' in cardDict['type'][0].split():
      cppFile.write('\n')
      cppFile.write('string '+className+'::GetImage() {\n')
      if 'Basic' in cardDict['type'][0].split():
         cppFile.write('\treturn "|'+cardDict['text'][0]+'|";\n')
      else:
         cppFile.write('\treturn "|'+className+'|";\n')
      cppFile.write('}\n')
      cppFile.write('\n')
      cppFile.write('void '+className+'::Play() {\n')
      cppFile.write('\tMoveLoc(thePlayer->bf);\n')
      cppFile.write('\tthePlayer->maxMana[colors::'+cardDict['text'][0]+']++;\n')
      cppFile.write('\tthePlayer->curMana[colors::'+cardDict['text'][0]+']++;\n')
      cppFile.write('}\n')
#     cppFile.write('\n')
#      cppFile.write('string '+className+'::GetImage() {\n')
#      cppFile.write('\tif(!tapped) {\n')
#      cppFile.write('\t\treturn "|'+cardDict['power']+'/'+cardDict['toughness']+'|";\n')
#      cppFile.write('\t}\n')
#      cppFile.write('\telse {\n')
#      cppFile.write('\t\treturn "\\\\'+cardDict['power']+'/'+cardDict['toughness']+'\\\\";\n')
#      cppFile.write('\t}\n')
#      cppFile.write('}\n')
   cppFile.write('\n')

   includes.append('#include \"'+className+'.h\"\n')
   selectCases.append('\t\tcase CardList::'+className+':\n\t\t\ttheCard = new '+className+'();\n\t\t\tbreak;\n')
   nameToIndex.append('\tnameToIndex[\"'+cardDict['name']+'\"] = '+str(options.cardnum)+';\n')
   options.cardnum += 1
   enumList.append('\t'+className+',\n')
#      enumList.append('\t\t'+className+'='+cardDict['id']+',\n')
#   elif "Land" in cardDict['type'][0].split():
#      if options.verbose:
#         print 'Writing header file ' + className+'.h'
#      headerFile = open(className+'.h', 'w')
#      headerFile.write('/*\n * '+className+'.h\n *\n * Autogenerated by generateCards.py\n *\tAuthor: dstuck\n*/\n')
#      headerFile.write('\n')
#      headerFile.write('#ifndef '+className.upper()+'_H_\n')
#      headerFile.write('#define '+className.upper()+'_H_\n')
#      headerFile.write('\n')
#      headerFile.write('#include \"Card_Land.h\"\n')
#      headerFile.write('\n')
#      headerFile.write('class '+className+': public Card_Land {\n')
#      headerFile.write('public:\n')
#      headerFile.write('\t'+className+'();\n')
#      headerFile.write('\tvirtual ~'+className+'();\n')
#      headerFile.write('\tstring GetImage();\n')
## Temp Land fix
#      headerFile.write('\tvoid Play();\n')
#      headerFile.write('};\n')
#      headerFile.write('\n')
#      headerFile.write('#endif /* '+className.upper()+'_H_ */\n')
#      headerFile.write('\n')
#
#      if options.verbose:
#         print 'Writing implementation file ' + className+'.cpp'
#      cppFile = open(className+'.cpp', 'w')
#      cppFile.write('/*\n * '+className+'.cpp\n *\n * Autogenerated by generateCards.py\n *\tAuthor: dstuck\n*/\n')
#      cppFile.write('\n')
#      cppFile.write('#include \"'+className+'.h\"\n')
#      cppFile.write('\n')
#      cppFile.write(className+'::'+className+'() {\n')
#      cppFile.write('\tKeywordVanilla();\n')
#      cppFile.write('\tid = '+cardDict['id']+';\n')
#      cppFile.write('\tname = \"'+cardDict['name'].replace('\\u00c6','Ae')+'\";\n')
#      if cardDict['cmc']:
#         cppFile.write('\tcmc = '+cardDict['cmc']+';\n')
#      else:
#         cppFile.write('\tcmc = 0;\n')
#      cppFile.write('\tisLand = true;\n')
#      if "Basic" in cardDict['type'][0].split():
#         cppFile.write('\tisBasic = true;\n')
#      if "Legendary" in cardDict['type'][0].split():
#         cppFile.write('\tisLegendary = true;\n')
#      if "Artifact" in cardDict['type'][0].split():
#         cppFile.write('\tisArtifact = true;\n')
#      for subtype in cardDict['type'][1].split():
#         cppFile.write('\tsubtype.push_back(\"'+subtype+'\");\n')
#      for text in cardDict['text']:
#         cppFile.write('\trulesText.push_back("'+text+'");\n')
#      for outerFlavor in cardDict['flavor']:
#         for flavorText in outerFlavor:
#            flavorText = flavorText.replace('\\u2014','--').rstrip('\n').replace('\"','\\\"').replace('\'','\\\'').rstrip()
#            cppFile.write('\tflavor.push_back(\"'+flavorText+'\");\n')
#      if cardDict['power']:
#         cppFile.write('\tpower = '+cardDict['power']+';\n')
#      else:
#         cppFile.write('\tpower = 0;\n')
#      if cardDict['toughness']:
#         cppFile.write('\ttoughness = '+cardDict['toughness']+';\n')
#      else:
#         cppFile.write('\ttoughness = 0;\n')
#      if cardDict['loyalty']:
#         cppFile.write('\tloyalty = '+cardDict['loyalty']+';\n')
#      else:
#         cppFile.write('\tloyalty = 0;\n')
#      cppFile.write('\tset = \"'+cardDict['set']+'\";\n')
#      cppFile.write('\trarity = \"'+cardDict['rarity']+'\";\n')
#      cppFile.write('\tcardNumber = '+cardDict['number']+';\n')
#      cppFile.write('\timage = \"'+cardDict['image'].replace('\\/','/')+'\";\n')
#      for color in cardDict['mana']:
#         print color
#         if isinstance(color, (int,long)):
#            cppFile.write('\tmana[colors::O]+='+color+'\n')
#         elif color=='W':
#            cppFile.write('\tmana[colors::W]++;\n')
#         elif color=='U':
#            cppFile.write('\tmana[colors::U]++;\n')
#         elif color=='B':
#            cppFile.write('\tmana[colors::B]++;\n')
#         elif color=='R':
#            cppFile.write('\tmana[colors::R]++;\n')
#         elif color=='G':
#            cppFile.write('\tmana[colors::G]++;\n')
#      cppFile.write('}\n')
#      cppFile.write('\n')
#      cppFile.write(className+'::~'+className+'() {\n')
#      cppFile.write('}\n')
#      cppFile.write('\n')
#      cppFile.write('string '+className+'::GetImage() {\n')
#      if 'Basic' in cardDict['type'][0].split():
#         cppFile.write('\treturn "|'+cardDict['text'][0]+'|";\n')
#      else:
#         cppFile.write('\treturn "|'+className+'|";\n')
#      cppFile.write('}\n')
#      cppFile.write('\n')
#      cppFile.write('void '+className+'::Play() {\n')
#      cppFile.write('\tMoveLoc(thePlayer->bf);\n')
#      cppFile.write('\tthePlayer->maxMana[colors::'+cardDict['text'][0]+']++;\n')
#      cppFile.write('\tthePlayer->curMana[colors::'+cardDict['text'][0]+']++;\n')
#      cppFile.write('}\n')
#      cppFile.write('\n')
#
#      includes.append('#include \"'+className+'.h\"\n')
#      selectCases.append('\t\tcase CardList::'+className+':\n\t\t\ttheCard = new '+className+'();\n\t\t\tbreak;\n')
#      nameToIndex.append('\tnameToIndex[\"'+cardDict['name']+'\"] = '+str(options.cardnum)+';\n')
#      options.cardnum += 1
#      enumList.append('\t'+className+',\n')
##      enumList.append('\t'+className+'='+cardDict['id']+'\n')
#   else:
#      print cardDict['type'][0] + " not implemented yet"

selectorMod = open('selectorMod.txt','w')
cardListMod = open('listMod.txt','w')
for string in includes:
   selectorMod.write(string)
for string in selectCases:
   selectorMod.write(string)
for string in nameToIndex:
   selectorMod.write(string)
for string in enumList:
   cardListMod.write(string)

