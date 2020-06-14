# Sequen10Cing
PIC10C Final Project Documentation:


Background Info:

Central Dogma: 
The central dogma of molecular biology describes the two-step process, transcription and translation, by which the information in genes flows into proteins: DNA → RNA → protein.

Transcription converts DNA into RNA (essentially the same but single stranded, and in the scope of this project T is replaced by U)

Translation converts RNA into protien, 3 nucleotides at a time : https://www.google.com/url?sa=i&url=http%3A%2F%2Fbiology.kenyon.edu%2Fcourses%2Fbiol114%2FChap05%2FChapter05.html&psig=AOvVaw0oTZy2I0BHCaxm-cxwtOZV&ust=1592247733984000&source=images&cd=vfe&ved=0CAIQjRxqFwoTCNifnpf_geoCFQAAAAAdAAAAABAD.

SNiP:
Single nucleotide polymorphisms, frequently called SNPs (pronounced “snips”), are the most common type of genetic variation among people. Each SNP represents a difference in a single DNA building block, called a nucleotide. For example, a SNP may replace the nucleotide cytosine (C) with the nucleotide thymine (T) in a certain stretch of DNA.


Deletion: a deletion removes a nucleotide, if it is not a multiple of 3, shifts the entire frame for translation so the protein product becomes completely different:deletions are responsible for diseases like cystic fibrosis.

Insertion: inserts 1 or a set of nucleotides. If it is not a multiple of 3, shifts the frame for translation for the sequence after the insertion.

Mutation info: https://evolution.berkeley.edu/evolibrary/article/0_0_0/mutations_03#:~:text=Deletions%20are%20mutations%20in%20which,DNA%20is%20lost%2C%20or%20deleted.&text=Since%20protein%2Dcoding%20DNA%20is,These%20changes%20are%20called%20frameshifts.

//How this is meant to be used//
Test out different sequences, mutate them, translate them, see how the protein changes.
Find the number of SNips b/w two sequences.



//Intro//

Initially my idea was as follows: 
- a class to store genomes of various organisms
- a function to take any sequence and transcribe and translate it
- a function to simulate different types of mutations and their effects (insertion/deletion)
- a function to look up a particular gene in the genome of an organism (doesn't need to be exact)
- a function to compare two genomes and see a % of relatedness

I first started looking into creating a program that compares a % relatedness. I naively thought that it would just be simply aligning two sequences and seeing the % difference. However, I promptly discovered that sequence alignment is a legitimate area of research in bioinformatics and there are different algorithms for sequence alignment: https://en.wikipedia.org/wiki/Sequence_alignment#Pairwise_alignment . I tried to look into simple ways of implementing these types of algorithms in cpp however this was beyond my scope of knowledge.

If I was not able to code sequence alignment, creating a class that stores the genomes of various organisms becomes obsolete as I would not be able to do useful comparisons between two genomes. So, I started to think on a smaller scale, on the DNA level.

Firstly, I had to decide how to handle DNA information: what data structure would I store it in? eg: ATCGCAGAGATCAGAT
Initially I though I could just use the string itself, as it is indexable and is essentially a sequential container (char array). However, if I was to implement a function that inserted/deleted single/chunks of nucleotides, it would not really be facilitated by this data structure (arrays).

I then thought about a vector, however this would only allow me to insert at the end, and requesting a new vector sized chunk of memory every time I wanted to insert a new nucleotide would not be practical.

I then looked to data structures that would insert/delete fast and instantly a List came to mind. Coding and insertion/ deletion function would be fairly easy as I would just need to change the addresses that pointers changed to. Iterating and indexing a list is not easily done as it is not a sequential container, however, the fact that I can insert/delete easily, would allow me to represent the dynamic nature of DNA very well. I also decided to use a doubly linked list do represent the reversibility of DNA (i.e can be read back and forth).

So finally, I had decided on a List to handle my DNA information. I then proceeded to implement my own list called "SEQUENCE", and my own type of nodes called "Nucleotide". A SEQUENCE would just be a string of NUCLEOTIDES.


//Development//


Implementing my own List and Node class was simple enough. The NUCLEOTIDE class just had a character (for the base) and two pointers, back and forth. My Sequence class would just have 2 NUCLEOTIDE pointers, one to the beginning of the list, one to the end of the list. 
One part of the class implementation that I struggled with was using an iterator. I tried to make a Sequence iterator class to make iterating through the sequences easy with the use of ++ and -- operators, however I soon realized that it would be much easier to just loop through each NUCLEOTIDE manually.

As I started to implement member functions, I kept running into issues of privacy despite making my two classes friends of each other. In my main function I wanted to change things around in the private members of my classes in order to test the functionality of my classes. Furthermore, I wanted to use helper functions for some of the member functions and thought the work around of writing accessor//mutator functions was not worth it so I just decided the make all the member functions and member variables of each class public. 

When creating the constructor for my SEQUENCE class, I new that I would be taking in the sequence as a string, parsing through the string and creating a new NUCLEOTIDE for each character in the string. I use the new keyword for every NUCLEOTIDE, so I knew that I would need to keep memory management in mind. 
I tried to use good coding practices and use SBRM by making the destructor of the SEQUENCE responsible for deleting all the NUCLEOTIDES, however I ran into some issues which I delve into below.

The hardest function that I had to implement was the find function. SNiP or Single Nucleotide Polymorphisms are sequences in DNA that differ by only one nucleotide, likely due to a mutation. SNiP's are a useful way of tracking phylogenies and how natural selection effects them as you can look for these small differences and deduce how an organism has changed over time. I wanted to implement a find function that did exactly that, given a smaller sequence, find all the indexes in the bigger sequence that contain the smaller one up to 1 nucleotide difference. I wanted to implement it in such a manner that the smaller sequence is tested against each nucleotide of the bigger sequence so that all possible comparisons are done. This is quite memory intensive however, I was not able to find a different way to implement it.
When actually coding the function, I realized how useful sequence containers were in doing comparisons as it is very easy to loop through then and align them through indexing. Adaptive containers, like my list, are not very good for comparisons and find functions, at least in my implementation as I also wanted to keep a count of the indexes where all the matches were. Essentially I was trying to implement sequence container functionality in an adaptive container. When coding the function, I realized I had to keep track of many things: the index, the pointer to the original sequence, pointer to the sequence being found, etc. I also ran into some memory management issues, for example, I not only had to ensure that none of my pointers reached a nullptr (end of the sequence) but also if the (next)^n pointer was not null, where n is the size of the sequence being compare. I was finally able to implement the function with the use of helper functions.



After implementing the find function, I ran into some issues with the destructor of the classes. When the the program ended, and the SEQUENCE destructors were called, I kept getting an error that said "pointer being freed was not allocated", however I ensured that there were no memory leaks in my functions as I would never declare a new Object in them. I would only declare a new Object in my constructor. Furthermore, when debugging, I found out that one of the sequences would destruct normally, but the other one would lead to a memory leak. I tried to debug this issue for a few hours (silver lining: I learnt how to use the debugger on XCODE) however I was not able to find the issue. I was looking into forums and found information that indicated that there might be an issue with the copy constructor: I could be trying to delete the copy an object twice: https://stackoverflow.com/questions/14457118/c-pointer-being-freed-was-not-allocated/14459959.
I tried to implement my own Copy ctor however the issue persisted. In a last resort effort, I made a delete function that took care of the deletion of all the NUCLEOTIDES of a sequence instead of making the destructor responsible for it. It contained the same exact code as the destructor. This seemed to work and I still am a little puzzled about this. If you could tell me what was wrong about my destructor it would be greatly appreciated (it is commented out in my code).


Another function that I found tricky to implement was the translation function. DNA contains the instructions to build proteins, and every 3 DNA nucleotides codes for a specific amino acid (proteins are chains of amino acids). When figuring out the protein sequence manually, one would use a codon chart : https://www.google.com/url?sa=i&url=http%3A%2F%2Fbiology.kenyon.edu%2Fcourses%2Fbiol114%2FChap05%2FChapter05.html&psig=AOvVaw0oTZy2I0BHCaxm-cxwtOZV&ust=1592247733984000&source=images&cd=vfe&ved=0CAIQjRxqFwoTCNifnpf_geoCFQAAAAAdAAAAABAD. DNA is read 3 sequences at a time, so there are 4^3 possible combinations.
I thought of various ways to implement this. One was a multidimensional map (a key to a key to a key to a key to a map), however I had a lot of difficulty with implementing this.
Another data structure i thought of implementing was a trie, however I found that quite complicated to implement as there is no inbuilt tree class in the standard cpp library. I finally and rather anticlimactically used a simple map with 64 key, value pairs. 


//What Ive learnt//

- As it was the end of the quarter and I am an international student, I had to ship my desktop PC. As a result I had to switch operating systems Windows->Mac. Surprisingly the only learning curve was using version control on git. However, now I am familiar with Visual Studio and Xcode.

-I learnt a lot about containers and the benefits of using different types of containers (Sequential vs Adaptive)

_I learnt a lot about debugging interestingly enough (step over, step in, etc)


//Future improvement//

-I would like to fix my destructor
-I would like to add some function to randomly mutate dna over various cycles and see the difference between the starting sequence and the ending sequence. I would account for the likelihood of different mutations.
