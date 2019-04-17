package main

import "math/rand"

// An Agent is an agent in a simulation.
type Agent interface {
	Positioned
	Update()
	Spawn() Agent
	Alive() bool
        String() string
	World() *World
	AcceptScent(s *Scent)
	AcceptTazzie(d *Tazzie)
	ActOn(a Agent)
}

type Inert struct {
}

func (i *Inert) ActOn(a Agent) {
}

// A Generic is a generic agent with a home world and a location.
type Generic struct {
	world *World
	Hex
}

func (g *Generic) ActOn(a Agent) {
}


// World returns the world a generic agent lives in.
func (g *Generic) World() *World {
	return g.world
}

// NewGeneric creates and returns a new generic at a random location in the given world.
func NewGeneric(world *World) Generic {
	return Generic{world, world.Random()}
}

// NoTazzieAction supplies a do-nothing AcceptTazzie function.
type NoTazzieAction struct {
}

func (a *NoTazzieAction) AcceptTazzie(d *Tazzie) {
}

// NoScentAction supplies a do-nothing AcceptScent function.
type NoScentAction struct {
}

func (a *NoScentAction) AcceptScent(s *Scent) {
}

// NoActions supplies do-nothing functions for interations with predators, prey, and scents.
type NoActions struct {
     NoTazzieAction
     NoScentAction
}

// EatenByTazzie supplies a AcceptTazzie method that sets a bool to false.
type EatenByTazzie struct {
	alive *bool
}

func (e *EatenByTazzie) AcceptTazzie(d *Tazzie) {
	*(e.alive) = false
}

// AcceptTazzie function with a Tazzie receiver, Tazzie argument, and no return value. Both the receiver and argument should be pointers. The argument will be the actor in the interaction and the receiver will be the patient. The new function should set the infected flag of the patient to true 20% of the time if the actor is infected.
func (patient *Tazzie) AcceptTazzie(actor *Tazzie) {
	if actor.infected && rand.Intn(5) == 1 {
		patient.infected = true
	}
}


// A Stationary is a Generic agent that also supplies a do-nothing Update function.
type Stationary struct {
	Generic
}

func (s *Stationary) Update() {
}

// A Mobile is a Generic agent that also supplies an Update function that moves the
// agent one step closer to a goal.  Agents that embed Mobile must supply a ReachedGoal
// function that determines what action to take when the agent reaches its goal.
type Mobile struct {
	Generic
	goal *Hex
	ReachedGoal func()
}

// Update updates the location of a Mobile agent to be one step closer to its current goal.
// When it reaches the goal, it calls the ReachedGoal function to determine the action
// to take.
func (s *Mobile) Update() {
	s.Closer(*(s.goal))
	r1, c1 := s.Position()
	r2, c2 := s.goal.Position()
	if r1 == r2 && c1 == c2 {
		s.ReachedGoal()
	}
}

// Immortal supplies an always-alive Alive function.
type Immortal struct {
}

func (i *Immortal) Alive() bool {
	return true
}

// NonEmitter supplies a spawn-nothing Spawn function.
type NonEmitter struct {
}

func (n *NonEmitter) Spawn() Agent {
	return nil
}

// ScentFollower supplies an AcceptScent function that changes an externally allocated
// Hex to the origin of the Scent.
type ScentFollower struct {
     goal *Hex
}

// AcceptScent changes the external goal to the origin of the Scent.
func (a *ScentFollower) AcceptScent(s *Scent) {
     *(a.goal) = s.Origin()
}

// Mortal supplies an Alive function that returns the value of an
// externally allocated boolean.
type Mortal struct {
     alive *bool
}

// Alive returns the value of the external alive field.
func (m *Mortal) Alive() bool {
	return *(m.alive)
}

// An Origined is something that has a starting location.
type Origined interface {
	Origin() Hex
}

// Emitted implements Origined by supplying a field to hold the origin.
type Emitted struct {
	origin Hex
}

func (e *Emitted) Origin() Hex {
	return e.origin
}

// A Scent is an Origined, Mobile, Mortal Agent that is spawned by an Agent.  It dies when
// it reaches the goal it randomly selects upon creation.
type Scent struct {
	Mobile
	NonEmitter
	Mortal
	Emitted
	NoActions
}

func (s *Scent) ActOn(a Agent) {
	a.AcceptScent(s)
}

// String returns "x" as the printable representation of a Scent.
func (s *Scent) String() string {
	return "x"
}

// NewScent returns a new Scent that starts at the location of the given Agent.
func NewScent(a Agent) *Scent {
	r, c := a.Position()
	origin := Hex{r, c}
	goal := a.World().RandomBorder()

	alive := true

	return &Scent{
		Mobile{
			Generic{a.World(), Hex{r, c}},
			&goal,
			func () { alive = false } },
		NonEmitter{},
		Mortal{&alive},
	        Emitted{origin},
		NoActions{} }
}

// Emitter supplies a Spawn function that spawns a new Agent at the rate given by the
// rate field.  The agent to be spawned is determined by the Emit function that embedding
// objects must supply.
type Emitter struct {
	rate int
	Emit func () Agent
}

// Spawn spawns an Agent at an average rate of once per whatever value is held in the rate
// field.  The Agent to spawn is determined by the Emit function.
func (e *Emitter) Spawn() Agent {
	if rand.Intn(e.rate) == 0 {
		return e.Emit()
	} else {
		return nil
	}
}

// FoodSource is a Stationay, Immortal Agent that emits Food on average
// once per 20 time steps
type FoodSource struct {
     Stationary
     Emitter
     Immortal
     NoActions
     Inert
}

func NewFoodSource(w *World) *FoodSource {
	source := FoodSource{
			Stationary{
				Generic{
				w,
				w.Random()} },
			Emitter{
				20,
				func () Agent { return NewFood(w, w.Random()) } },
			Immortal{},
			NoActions{},
			Inert{} }
	return &source
}

// String returns "*" as the printable representation of Food.
func (s *FoodSource) String() string {
	return ""
}


// Food is a Stationary, Mortal Agent that emits Scents on average once per 5 time steps
// and dies when it is eaten by a Tazzie.
type Food struct {
	Stationary
	Emitter
	Mortal
	EatenByTazzie
	NoScentAction
	Inert
}

// String returns "*" as the printable representation of Food.
func (f *Food) String() string {
	return "*"
}

// NewFood returns a new Food at a randomly chosen location in the world.
func NewFood(w *World, pos Hex) *Food {
	alive := true

	f := Food{
		Stationary{
			Generic{
				w,
				pos} },
		Emitter{
			5,
			nil },
		Mortal{&alive},
		EatenByTazzie{&alive},
		NoScentAction{},
		Inert{} }
	f.Emit = func () Agent { return NewScent(&f) }

	return &f
}

// A Tazzie is a Mobile, Mortal agent that emits nothing, follows scents,
// and passes infections to other tazzies
type Tazzie struct {
	Mobile
	NonEmitter
	Immortal
	ScentFollower
	infected bool
}

func (d *Tazzie) ActOn(a Agent) {
	a.AcceptTazzie(d)
}

// String returns "p" as the printable representation of a Tazzie.
func (d *Tazzie) String() string {
     if d.infected {
     	return "b"
     } else {
        return "d"
     }	
     
}


// NewTazzie creates and returns a new Tazzie at a randomly chosen location and with a randomly
// chosen goal.
func NewTazzie(w *World, i bool) *Tazzie {
	goal := w.Random()
	p := Tazzie{
		Mobile{
			NewGeneric(w),
			&goal,
			func () { goal.Copy(w.Random()) }} ,
		NonEmitter{},
		Immortal{},
		ScentFollower{&goal},
		i}

	return &p
}

type Automobile struct{
	Mobile
	Emitter
	Mortal
	NoActions
	Inert
}

func (a *Automobile) String() string {
	return "A"
}

func NewAutomobile(w *World, start Hex, end Hex) Agent {
	alive:=true
	auto:=Automobile{
		Mobile{Generic{w, start}, &end, func() {alive = false} },
		Emitter{15, nil},
		Mortal{&alive},
		NoActions{},
		Inert{},
	}
	auto.Emit = func() Agent{ return NewFood(w, auto.Hex)}
	return &auto
}


