
dictionary = set(['siema', 'arbuz', 'buz', 'luz', 'maar',
                  'buzbuz', 'luzbluz', 'maluz', 'filo', 'ma', 'arbuziol'])

maxWordLength = 10


def maxSquareLength(text):
    print(text)
    dp = [0]*(len(text)+3)
    words = [0]*(len(text)+3)
    for i in range(len(text)+1):
        if i < maxWordLength:
            # print("sprawdzam:",text[0:i+1], i)
            if text[0:i+1] in dictionary:
                # print("weszlo")
                dp[i] = (i+1)**2
                words[i] = i+1
        for j in range(i, max(-1, i-maxWordLength), -1):
         # print(text[j:i+1], j, i+1)
            if text[j: i + 1] in dictionary and dp[j - 1] != 0:
                if dp[j-1] + (i-j+1)**2 > dp[i]:
                    words[i] = i-j+1
                dp[i] = max(dp[i], dp[j-1]+(i-j+1)**2)

    i = len(text)-1

    res_temp = []
    print(words)
    while i >= 0:
        # print(text[i-words[i]+1:i+1])
        if words[i] == 0:
            res_temp.append(text[i:i+1])
            i -= 1
        else:
            res_temp.append(text[i-words[i]+1:i+1])
            i -= words[i]

    res_temp.reverse()

    return res_temp


maxSquareLength('siemabuzarbuzbuzmaarbuziol')
