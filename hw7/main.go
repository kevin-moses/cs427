package main

import (
	"fmt"
	"bufio"
	"os"
	"math"
	"strconv"
	// "strings"
)

func testInfection() {
	w := NewWorld(12, 0, 0)
	t1 := NewTazzie(w, true)
	t2 := NewTazzie(w, false)

	for i := 0; i < 100; i++ {
		t2.ActOn(t1)
	}

	if t2.String() == "b" {
		fmt.Println("FAILED -- infection spreads when uninfected acts on infected")
		return
	} else if t1.String() != "b" {
		fmt.Println("FAILED -- infection cured")
		return
	}

	infections := 0
	trials := 10000
	rate := 0.2
	expected := float64(trials) * rate
	stddev := math.Sqrt(expected * (1 - rate))
	for i := 0; i < trials; i++ {
		t3 := NewTazzie(w, true)
		t4 := NewTazzie(w, false)

		t3.ActOn(t4)

		if t4.String() == "b" {
			infections++
		}
		if t3.String() != "b" {
			fmt.Println("FAILED -- infetion cured")
			return
		}
	}

	if float64(infections) > expected + 3 * stddev {
		fmt.Println("FAILED -- infection rate too high")
		return
	} else if float64(infections) < expected - 3 * stddev {
		fmt.Println("FAILED -- infection rate too low")
		return
	}

	fmt.Println("PASSED")
}

func testUpdateAutomobile() {
	w := NewWorld(12, 0, 0)
	auto := NewAutomobile(w, Hex{3, 0}, Hex{3, 10})

	r, c := auto.Position()
	if r != 3 || c != 0 {
		fmt.Println("FAILED -- initial position is (", r, ",", c, ") not (3, 0)")
		return
	}
	
	auto.Update()
	r, c = auto.Position()
	if r != 3 || c != 1 {
		fmt.Println("FAILED -- next position is (", r, ",", c, ") not (3, 1)")
		return
	}

	auto.Update()
	r, c = auto.Position()
	if r != 3 || c != 2 {
		fmt.Println("FAILED -- next next position is (", r, ",", c, ") not (3, 2)")
		return
	}
	
	fmt.Println("PASSED")
}

func testKillAutomobile() {
	w := NewWorld(12, 0, 0)
	auto := NewAutomobile(w, Hex{3, 0}, Hex{3, 1})

	auto.Update()
	if auto.Alive() {
		fmt.Println("FAILED -- Automobile still alive after reaching goal")
		return
	}
	
	fmt.Println("PASSED")
}

func testAutomobileSpawn() {
	w := NewWorld(12, 0, 0)
	ar, ac := 3, 0
	auto := NewAutomobile(w, Hex{ar, ac}, Hex{ar, ac + 1})
	testSpawn(auto, 1.0 / 15.0, "*", func (r int, c int) bool { return r == ar && c == ac })
}

func testSpawn(a Agent, rate float64, kind string, verifyLocation func(r int, c int) bool) {
	trials := 10000
	expected := float64(trials) * rate
	stddev := math.Sqrt(expected * (1 - rate))
	spawns := 0
	for i := 0; i < trials; i++ {
		s := a.Spawn()

		if s != nil {
			spawns++
			if s.String() != kind {
				fmt.Println("FAILED -- spawned", s)
				return
			} else {
				r, c := s.Position()
				if !verifyLocation(r, c) {
					ar, ac := a.Position()
					fmt.Println("FAILED -- agent at (", ar, ",", ac, ") spawned", s, "at (", r, ",", c, ")")
					return
				}
			}
		}
	}

	if float64(spawns) > expected + 3 * stddev {
		fmt.Println("FAILED -- spawn rate too high")
		return
	} else if float64(spawns) < expected - 3 * stddev {
		fmt.Println("FAILED -- spawn rate too low")
		return
	}

	fmt.Println("PASSED")
}

// func testUpdateRoad() {
// 	w := NewWorld(12, 0, 0)
// 	road := NewRoadEnd(w, Hex{3, 0}, Hex{3, 10})

// 	r, c := road.Position()
// 	if r != 3 || c != 0 {
// 		fmt.Println("FAILED -- initial position is (", r, ",", c, ") not (3, 0)")
// 		return
// 	}
	
// 	road.Update()
// 	r, c = road.Position()
// 	if r != 3 || c != 0 {
// 		fmt.Println("FAILED -- next position is (", r, ",", c, ") not (3, 0)")
// 		return
// 	}

// 	fmt.Println("PASSED")
// }

// func testKillRoad() {
// 	w := NewWorld(12, 0, 0)
// 	road := NewRoadEnd(w, Hex{3, 0}, Hex{3, 1})

// 	for i := 0; i < 1000000; i++ {
// 		road.Update()
// 		if !road.Alive() {
// 			fmt.Println("FAILED -- RoadEnd dies")
// 			return
// 		}
// 	}
	
// 	fmt.Println("PASSED")
// }

// func testRoadSpawn() {
// 	w := NewWorld(12, 0, 0)
// 	rr, rc := 3, 0
// 	road := NewRoadEnd(w, Hex{rr, rc}, Hex{rr, rc + 1})
// 	testSpawn(road, 1.0 / 25.0, "A", func (r int, c int) bool { return r == rr && c == rc })
// }

// func testUpdateSpawnedAutomobile() {
// 	w := NewWorld(12, 0, 0)
// 	road := NewRoadEnd(w, Hex{5, 0}, Hex{5, 10})
	
// 	auto := road.Spawn()
// 	for auto == nil {
// 		auto = road.Spawn()
// 	}
	
// 	auto.Update()

// 	r, c := auto.Position()
// 	if r != 5 || c != 1 {
// 		fmt.Println("FAILED -- spawned Automobile's updated position is (", r, ",", c, ") not (5, 1)")
// 		return
// 	}

// 	for auto.Alive() {
// 		auto.Update()
// 	}
// 	r, c = auto.Position()
// 	if r != 5 || c != 10 {
// 		fmt.Println("FAILED -- spawned Automobile's last position is (", r, ",", c, ") not (5, 10)")
// 		return
// 	}

// 	fmt.Println("PASSED")
// }

// func testCountCars() {
// 	w := NewWorld(12, 0, 0)

// 	cars := 0
// 	for i := 0; i < 750; i++ {
// 		w.Update();
// 		display := w.String()

// 		cars += strings.Count(display, "A")
// 	}

	// expect more cars, but some may be hidden
	// have no idea why I can't run more 1000 iterations in the scripts
	// error is below
	/*
pthread_create failed: 11
fatal error: pthread_create

runtime stack:
runtime_throw
	../../../libgo/runtime/panic.c:13
runtime_mstart
	../../../libgo/runtime/proc.c:527

goroutine 1 [running]:
main.Hex.Closer
	/tmp/.glenn.james.jrg941515/position.go:46
main.Mobile.Update
	/tmp/.glenn.james.jrg941515/agents.go:94
main.World.Update
	/tmp/.glenn.james.jrg941515/world.go:53
main.testCountCars
	/tmp/.glenn.james.jrg941515/main.go:218
main.main
	/tmp/.glenn.james.jrg941515/main.go:275
// */
// 	if cars < 200 {
// 		fmt.Println("FAILED -- saw only", cars, "Automobiles in the world")
// 	} else {
// 		fmt.Println("PASSED")
// 	}
// }

func simulate(step func()) {
	w := NewWorld(15, 7, 1)
	for i := 0; i < 5000; i++ {
		fmt.Println(w)
		w.Update()
		fmt.Println()

		step()
	}
	fmt.Println(w)
}

func main() {
	args := os.Args[1:]

	if len(args) > 0 && args[0] == "-test" {
		if len(args) == 1 {
			fmt.Println(os.Args[0], ": Missing test number")
		} else {
			testNum, err := strconv.Atoi(args[1])
			if err != nil {
				fmt.Println(os.Args[0], ": Invalid test number: ", args[1])
			} else if testNum == 0 {
				testInfection()
				
			} else if testNum == 1 {
				testUpdateAutomobile()
			} else if testNum == 2 {
				testKillAutomobile()
			} else if testNum == 3 {
				testAutomobileSpawn()
			// } else if testNum == 4 {
			// 	// testUpdateRoad()
			// } else if testNum == 5 {
			// 	// testKillRoad()
			// } else if testNum == 6 {
			// 	// testRoadSpawn()
			// } else if testNum == 7 {
			// 	// testUpdateSpawnedAutomobile()
			// } else if testNum == 8 {
			// 	simulate( func () {} )
			// 	fmt.Println("PASSED")
			// } else if testNum == 9 {
			// 	testCountCars()
			} else {
				fmt.Println(os.Args[0], ": Invalid test number: ", args[1])
			}
		}
	} else {
		in := bufio.NewReader(os.Stdin)
		simulate( func() { in.ReadString('\n')} )
	}
}
