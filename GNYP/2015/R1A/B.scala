import scala.io.Source

def solve(caseNum:Int, line:String, pos:Int):Unit = {
    var numbers = line.split(' ').map(ch => ch.toLong)
    val n = numbers.length
    var myPos = pos.toLong
    var l = 1.toLong; var r = numbers.max * myPos.toLong + 1
    def getNumber(tms:Long):Long = {
        var sum = 0.toLong
        numbers.foreach { x => sum += (tms + x - 1) / x }
        sum
    }
    while (l <= r) {
        val mid = (l + r) / 2
        if (getNumber(mid) >= myPos) {
            r = mid - 1
        } else {
            l = mid + 1
        }
    }
    val serveTime = r.toLong + 1
    var minLeft = numbers.max.toLong + 1
    numbers.foreach { x =>
        val tm = {
            if (serveTime % x == 0) x
            else serveTime % x
        }
        minLeft = math.min(minLeft, tm)
        myPos -= (serveTime - tm) / x
    }
    numbers.foreach { x => 
        val tm = {
            if (serveTime % x == 0) x
            else serveTime % x
        }
        if (tm > minLeft) {
            myPos -= 1
        }
    }
    var cnt = 0; var res = -1
    for (idx <- 0 until n) {
        val tm = {
            if (serveTime % numbers(idx) == 0) numbers(idx)
            else serveTime % numbers(idx)
        }
        // println(idx, tm)
        if (tm == minLeft) {
            cnt += 1
            if (cnt == myPos) {
                res = idx + 1
            }
        }
    }
    println("Case #" + caseNum + ": " + res)
}

var caseNum = 0
var mypos = 0
Source.fromFile("B.in").getLines.foreach { line =>
    if (caseNum != 0) {
        if (caseNum % 2 == 0) {
            solve(caseNum / 2, line, mypos)
        } else {
            val arr = line.split(' ').map(ch => ch.toInt)
            mypos = arr(1)
        }
    }
    caseNum += 1
}
