int trap(int* height, int heightSize) {
    int max_height;
    int max_index;
    int i;
    int sum = 0;

    max_height = 0;
    for(i = 0; i < heightSize; ++i)
        if(height[i] > max_height){
            max_index = i;
            max_height = height[i];
        }

    max_height = 0;
    for(i = 0; i < max_index; ++i){
        if(max_height > height[i])
            sum += (max_height - height[i]);
        max_height = height[i] > max_height ? height[i] : max_height;
    }

    max_height = 0;
    for(i = heightSize - 1; i > max_index; --i){
        if(max_height > height[i])
            sum += (max_height - height[i]);
        max_height = height[i] > max_height ? height[i] : max_height;
    }

    return sum;
}
