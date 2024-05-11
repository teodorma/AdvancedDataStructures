# Advanced Data Structure Performance Comparison

## Introduction

This project explores the performance of several well-known advanced data structures algorithms across different datasets. The objective is to comprehend the behavior of each data structure under varying conditions and discern their respective strengths and weaknesses. Such an analysis serves as a compass for algorithm selection in real-world software development scenarios, where sorting efficiency plays a pivotal role in determining application performance.

## Data Structure Under Test

We compare the performance of the following three data structure:

- **Skip List**: A probabilistic data structure that enables fast search, insertion, and deletion operations, often used in scenarios where balanced trees might be overly complex or unnecessary.
- **Red-Black Tree**: A self-balancing binary search tree with strong balance guarantees, ensuring logarithmic time complexity for search, insertion, and deletion operations. Its balancing rules prioritize overall tree balance over strict adherence to height balance.
- **AVL Tree**: Another self-balancing binary search tree that maintains strict balance, offering logarithmic time complexity for all operations. Unlike Red-Black Tree, AVL Tree strictly adheres to height balance, ensuring that the difference in heights between left and right subtrees is always within a defined range.

## Performance Evaluation

To evaluate the performance of these data structures, we conducted a series of tests varying the datasets. Below are the tables and diagrams showing the execution times of the required operations, where we have:
- 1: insert the number X into the set
- 2: delete the number X from the set (if it exists)
- 3: display 1 if the number X is in the set, otherwise display 0
- 4: display the largest number Y, less than or equal to X
- 5: display the smallest number Y, greater than or equal to X
- 6: display in sorted order all the Z numbers, where X ≤ Z ≤ Y

For the following tables, the numbers were generated as:

- increasing

![Tablea1](https://github.com/teodorma/Sorting_Algorithms/assets/127875348/29cab45f-1315-4ed6-8d3a-0c856c245daf)

- decreasing

![Tablea2](https://github.com/teodorma/Sorting_Algorithms/assets/127875348/875260aa-6e37-4d51-8c95-5fe274cb852a)

- random

![Tablea3](https://github.com/teodorma/Sorting_Algorithms/assets/127875348/8d8c606e-21f2-41aa-9fb0-223b1a2be823)

Also, below we have diagrams for each data structure where the difference can be observed when generating random, increasing, and decreasing numbers for each operation.


![WhatsApp Image 2024-05-11 at 15 17 32_fab12f5c](https://github.com/teodorma/Sorting_Algorithms/assets/127875348/5f7e65b1-76c1-46b6-b840-e347f89504df)

![WhatsApp Image 2024-05-11 at 15 17 32_a4b78856](https://github.com/teodorma/Sorting_Algorithms/assets/127875348/48f8a879-3d1f-47b4-801e-1a510894a683)

![WhatsApp Image 2024-05-11 at 15 17 32_236b1924](https://github.com/teodorma/Sorting_Algorithms/assets/127875348/d3749842-87d0-4523-b7a5-5e70e2825a03)




## Key Findings

- **Skip List**: Demonstrates excellent performance in search, insertion, and deletion operations, especially in scenarios where maintaining strict balance is not a priority. Its probabilistic nature allows for efficient handling of large datasets and varying element distributions. However, its performance might degrade slightly in highly balanced or ordered datasets.
- **Red-Black Tree**: Shows robust performance across various datasets, offering logarithmic time complexity for search, insertion, and deletion operations. Its strong balance guarantees make it particularly suitable for applications where maintaining overall tree balance is essential. However, the overhead associated with enforcing these balance rules may slightly affect performance compared to Skip List and AVL Tree in certain scenarios.
- **AVL Tree**: Exhibits consistent efficiency in maintaining strict height balance, ensuring logarithmic time complexity for all operations. Its rigid balancing requirements make it well-suited for applications where maintaining precise height balance is crucial. However, the stricter balancing rules may result in slightly higher overhead compared to Skip List and Red-Black Tree, particularly in insertion and deletion operations.

These key findings highlight the strengths and weaknesses of Skip List, Red-Black Tree, and AVL Tree across different datasets and scenarios. While Skip List offers flexibility and efficiency in probabilistic balancing, Red-Black Tree and AVL Tree provide strong balance guarantees, each catering to specific requirements in real-world software development.


## Conclusion

In conclusion, Skip List, Red-Black Tree, and AVL Tree each offer unique benefits. Skip List excels in probabilistic balancing, while Red-Black Tree prioritizes overall balance, and AVL Tree focuses on strict height balance. The choice depends on specific application requirements, with Skip List offering flexibility, Red-Black Tree providing robust performance, and AVL Tree ensuring precise balance.

