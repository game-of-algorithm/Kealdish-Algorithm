/**
 * 插值法查找。假设符号表的键支持算术操作。编写二分查找来模拟字典的行为，再与插值法查找进行对比
 */

/**
 * 其实就是对二分查找的变形和改进。
 * 二分查找中 mid = low + (high - low) * 1/2
 * 插值查找中 mid = low + (high - low) * (key - a[low])/(a[high] - a[low])
 * 对于均匀数组而言，会显著减少比较次数，
 * 但是对于分部不均匀数组而言，提升不明显。
 */