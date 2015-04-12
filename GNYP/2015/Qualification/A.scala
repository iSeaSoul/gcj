import scala.io.Source

def solve(caseNum:Int, line:String):Unit = {
    var num = 0; var res = 0; var pos = 0
    line.split(' ')(1).foreach {ch =>
        val cnt = ch.toInt - '0'.toInt
        if (cnt != 0) {
            if (pos > num) {
                res += pos - num
                num = pos + cnt
            } else {
                num += cnt
            }
        }
        pos += 1
    }
    println("Case #" + caseNum + ": " + res)
}

var caseNum = 0
Source.fromFile("A.in").getLines.foreach {line =>
    if (caseNum != 0) {
        solve(caseNum, line)
    }
    caseNum += 1
}
