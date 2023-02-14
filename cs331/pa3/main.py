#Name: Allen Chan
#Program Assignment 3

import sys, string, math

trainingSet = sys.argv[1]
testSet = sys.argv[2]

class bayesNode():
	def __init__(self, word):
		self.word = word
		self.pos = self.neg = 0
		self.chance = {}

def createWordBank(file):
	wordBank = []

	with open(file, "r") as fp1:
		Lines = fp1.readlines()
		for line in Lines:
			removedPunc = sepPunc(line).lower().split('\t')
			wordBank += removedPunc[0].split(' ')    			

	bank = sorted(list(set(wordBank)))

	return bank

#preproccessed files
def preProc(file, wordBank):
	fp1 = open(file, "r")
	val = []
	lenWordBank = len(wordBank)

	#loop through every line in file
	with open(file, "r") as fp1:
		Lines = fp1.readlines()
		for line in Lines:
			#remove punctuation
			line = sepPunc(line).strip().split()

			#create array length of word bank
			arr1 = [0] * lenWordBank

			#inser label in last slot
			arr1[lenWordBank - 1] = int(line[-1].strip())

			i = 0
			while i < lenWordBank:
				for j in line:
					#check if word matches the one in word bank
					if j == wordBank[i]:
						arr1[i] = 1
				i = i + 1

			#add sentence to arr
			val.append(arr1)


	return val

def sepPunc(sent):
	convert = str.maketrans('', '', string.punctuation)
	sent = sent.translate(convert)

	return sent

def createNewFiles(testData, trainingData):
	fp1 = open("preprocessed_train.txt", "a")

	for line in trainingData:
		fp1.write(str(line)[1:-1] + "\n")
	fp1.close()

	fp2 = open("preprocessed_test.txt", "a")

	for line in testData:
    		fp2.write(str(line)[1:-1] + "\n")
	fp2.close()

def calcWordChance(wordBank, features):
	node = {}
	ff = 0
	ft = 0
	tf = 0
	tt = 0

	#loop through each word and their index in the word bank
	for idx, word in enumerate(wordBank):
    	#create bayes node object along with their corresponding word and index
		bayesN = bayesNode(word)
		
		#loop through each feature
		for feature in features:
			if int(feature[-1]) == 1:
    			#calculate positives
				bayesN.pos = bayesN.pos + 1

				if int(feature[idx]) == 0:
					ft = ft + 1
				else:
					tt = tt + 1

			else:
				#calculate negatives
				bayesN.neg = bayesN.neg + 1

				if int(feature[idx]) == 0:
					ff = ff + 1
				else:
					tf = tf + 1

		#calculate all the probabilities and insert in array				
		bayesN.chance = [[float(float(ff + 1)/float(bayesN.neg + 2)), float(float(ft + 1)/float(bayesN.pos + 2))], [float(float(tf + 1)/float(bayesN.neg + 2)), float(float(tt + 1)/float(bayesN.pos + 2))]]
		
		node[word] = bayesN

	return node

def classification(wordBank, bayesData, feature, pos, neg):
    #loop through all the words in the wordBank
	lenWordBank = len(wordBank)
	for idx in range(lenWordBank):
		data = bayesData[wordBank[idx]]
		featureInt = feature[idx]

		neg = neg + math.log10(float(data.chance[int(featureInt)][0]))
		pos = pos + math.log10(float(data.chance[int(featureInt)][1]))

	#check if it should return 1 or 0
	if pos >= neg:
		return 1
	else:
		return 0

def calcAcc(wordBank, values, bayesData):
	totalNumPred = 0
	totalNum = 0

	#label count
	numPos = bayesData[wordBank[0]].pos
	numNeg = bayesData[wordBank[0]].neg

	prob = numPos / (numPos + numNeg)

	#chance that any feature is positive or negative
	posProb = math.log10(prob)
	negProb = math.log10(prob)
	
	#loop through each value to check if it is correct
	for val in values:
		totalNumPred = totalNumPred + 1

		#check if the prediction value is equal to real value
		if classification(wordBank, bayesData, val, posProb, negProb) == int(val[-1]):
			totalNum = totalNum + 1

	accuracy = str(float(totalNum / totalNumPred) * 100)

	
	f = float(accuracy)
	formatAccuracy = "{:.2f}".format(f)

	return formatAccuracy

def printAcc(formatAccuracy):
    #open and write in results.txt
	results = open("results.txt", "a+")
	
	print("Trained using " + sys.argv[1] + " and " + sys.argv[2])
	results.write("Trained using " + sys.argv[1] + " and " + sys.argv[2] + "\n")

	print('Accuracy: ' + formatAccuracy + '%\n')
	results.write('Accuracy: ' + formatAccuracy + '%\n\n')
	
	results.close()

def main():
	#create a word bank from trainingset and testSet
	trainedBank = createWordBank(trainingSet)
	testingBank = createWordBank(testSet)

	trainedBank.append('classLabel')
	testingBank.append('classLabel')
	
	#preprocess the data from both files
	trainedVal = preProc(trainingSet, trainedBank)
	testVal = preProc(testSet, testingBank)
	
	#calculate probability 
	bayesData = calcWordChance(trainedBank, trainedVal)
	
	#calculate the accuracy
	formatAccuracy = calcAcc(trainedBank, trainedVal, bayesData)
	printAcc(formatAccuracy)
	
	formatAccuracy = calcAcc(trainedBank, testVal, bayesData)
	printAcc(formatAccuracy)

	#add words to the front
	trainedVal.insert(0, trainedBank)
	testVal.insert(0, testingBank)

	#put values in file
	createNewFiles(trainedVal, testVal)

if __name__ == "__main__":
	main()