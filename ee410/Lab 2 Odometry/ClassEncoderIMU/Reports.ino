

void LogoPrint() {
    Serial1.print(left_cnt);
    Serial1.write(9);
    Serial1.print(right_cnt);
    Serial1.write(9);
    Serial1.print(leftDuty);
    Serial1.write(9);
    Serial1.println(rightDuty);  
}
