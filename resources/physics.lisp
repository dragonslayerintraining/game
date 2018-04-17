(import "resources/gui.lisp")
(import "resources/bounds.lisp")
(defvar time)

(defun get-time () time)

(defun init ()
  (gui-init)
  (let ((ent (game-entity-summon)))
    (game-entity-setattr ent "x" 2400)
    (game-entity-setattr ent "y" 1000)
    (game-entity-setattr ent "size" 50)
    (game-entity-setattr ent "xdir" 0)
    (game-entity-setattr ent "ydir" 0)
    (game-entity-setattr ent "max-health" 10)
    (game-entity-setattr ent "health" 10)
    (game-entity-setattr ent "damage" 1)
    (game-entity-setattr ent "mass" 100)
    (game-entity-setattr ent "color" "ff0000")
    (game-entity-setattr ent "team" "red")
    (game-entity-setattr ent "type" "player")
    (game-entity-setattr ent "bounds" "bounce")
    (game-entity-setattr ent "firing" "slow")
    (game-entity-setattr ent "control" "player2")
    '(game-entity-setattr ent "vacuum" 't)
    )
  (let ((ent (game-entity-summon)))
    (game-entity-setattr ent "x" 800)
    (game-entity-setattr ent "y" 1000)
    (game-entity-setattr ent "size" 50)
    (game-entity-setattr ent "xdir" 0)
    (game-entity-setattr ent "ydir" 0)
    (game-entity-setattr ent "max-health" 10)
    (game-entity-setattr ent "health" 10)
    (game-entity-setattr ent "damage" 1)
    (game-entity-setattr ent "mass" 100)
    (game-entity-setattr ent "color" "00ff00")
    (game-entity-setattr ent "team" "green")
    (game-entity-setattr ent "type" "player")
    (game-entity-setattr ent "bounds" "bounce")
    (game-entity-setattr ent "firing" "slow")
    (game-entity-setattr ent "control" "player1")
    '(game-entity-setattr ent "vacuum" 't)
    )
  '(let ((ent (game-entity-summon)))
    (game-entity-setattr ent "x" 1600)
    (game-entity-setattr ent "y" 1000)
    (game-entity-setattr ent "size" 500)
    (game-entity-setattr ent "xdir" 0)
    (game-entity-setattr ent "ydir" 0)
    (game-entity-setattr ent "max-health" 1000)
    (game-entity-setattr ent "health" 1000)
    (game-entity-setattr ent "damage" 1)
    (game-entity-setattr ent "mass" 1000)
    (game-entity-setattr ent "color" "808080")
    (game-entity-setattr ent "team" "gray")
    (game-entity-setattr ent "type" "rock")
    (game-entity-setattr ent "bounds" "bounce")
    (game-entity-setattr ent "control" "none"))
  (let ((ent (game-entity-summon)))
    (game-entity-setattr ent "x" 1600)
    (game-entity-setattr ent "y" 1000)
    (game-entity-setattr ent "size" 10)
    (game-entity-setattr ent "xdir" 0)
    (game-entity-setattr ent "ydir" 0)
    (game-entity-setattr ent "max-health" 1000)
    (game-entity-setattr ent "health" 1000)
    (game-entity-setattr ent "damage" 1)
    (game-entity-setattr ent "mass" 100)
    (game-entity-setattr ent "color" "808080")
    (game-entity-setattr ent "team" "gray")
    (game-entity-setattr ent "type" "rock")
    (game-entity-setattr ent "bounds" "bounce")
    (game-entity-setattr ent "control" "fly"))
  )
(defun init-entity (ent)
  (game-entity-setattr ent "xdir" 0)
  (game-entity-setattr ent "ydir" 0))
(defun step ()
  (if (not time) (setq time 0)
    (setq time (+ 1 time)))
  (if (== (% time 100) 0)
      '(let ((ent (game-entity-summon)))
	(game-entity-setattr ent "x" 2400)
	(game-entity-setattr ent "y" 1000)
	(game-entity-setattr ent "size" 50)
	(game-entity-setattr ent "xdir" 0)
	(game-entity-setattr ent "ydir" 0)
	(game-entity-setattr ent "max-health" 100)
	(game-entity-setattr ent "health" 100)
	(game-entity-setattr ent "damage" 1)
	(game-entity-setattr ent "mass" 100)
	(game-entity-setattr ent "color" "ff00ff")
	(game-entity-setattr ent "team" "red")
	(game-entity-setattr ent "type" "player")
	(game-entity-setattr ent "bounds" "halt")
	(game-entity-setattr ent "firing" "slow")
	(game-entity-setattr ent "control" "fly")
	(game-entity-setattr ent "vacuum" 't)))
  (if (== (% time 100) 0)
      '(let ((ent (game-entity-summon)))
	(game-entity-setattr ent "x" 800)
	(game-entity-setattr ent "y" 1000)
	(game-entity-setattr ent "size" 50)
	(game-entity-setattr ent "xdir" 0)
	(game-entity-setattr ent "ydir" 0)
	(game-entity-setattr ent "max-health" 100)
	(game-entity-setattr ent "health" 100)
	(game-entity-setattr ent "damage" 1)
	(game-entity-setattr ent "mass" 100)
	(game-entity-setattr ent "color" "ffff00")
	(game-entity-setattr ent "team" "green")
	(game-entity-setattr ent "type" "player")
	(game-entity-setattr ent "bounds" "halt")
	(game-entity-setattr ent "firing" "slow")
	(game-entity-setattr ent "control" "fly")
	(game-entity-setattr ent "vacuum" 't))))
(defun game-entity-damage (ent dmg)
  (game-entity-setattr ent "health"
		       (- (game-entity-getattr ent "health") dmg))
  (if (<= (game-entity-getattr ent "health") 0)
      (game-entity-kill ent))
  (if (> (game-entity-getattr ent "health") (game-entity-getattr ent "max-health"))
      (game-entity-setattr ent "health" (game-entity-getattr ent "max-health"))))
(defun step-entity (ent)
  (gui-modify-vel ent)
  (game-bounds-apply ent)
  (let ((xdir (game-entity-getattr ent "xdir"))
	(ydir (game-entity-getattr ent "ydir")))
    (let ((magn (/ (pyth (double xdir) (double ydir)) 10)))
      '(if (> magn 1)
	  (progn
	    (game-entity-setattr ent "xdir" (int (/ xdir magn)))
	    (game-entity-setattr ent "ydir" (int (/ ydir magn)))))))
  (if (string-equals (game-entity-getattr ent "type") "player")
      (let ((xdir (game-entity-getattr ent "xdir"))
	    (ydir (game-entity-getattr ent "ydir")))
	(game-entity-setattr ent "xdir" (int (* 0.7 xdir)))
	(game-entity-setattr ent "ydir" (int (* 0.7 ydir)))))
  (let ((xdir (game-entity-getattr ent "xdir"))
	(ydir (game-entity-getattr ent "ydir")))
    (game-entity-setattr ent "x" (+ xdir (game-entity-getattr ent "x")))
    (game-entity-setattr ent "y" (+ ydir (game-entity-getattr ent "y")))))
(defun collide-entities (ent1 ent2)
  (if (and (game-entity-exists ent1) (game-entity-exists ent2))
      (progn
	(let ((ent1creator (game-entity-getattr ent1 "creator"))
	      (ent2creator (game-entity-getattr ent2 "creator")))
	  (if (not (equals ent1creator ent2creator))
	      (progn
		(if (and ent1creator (not (equals ent1creator ent2)) (game-entity-getattr ent1creator "vacuum"))
		    (game-entity-setattr ent2 "target" ent1creator))
		(if (and ent2creator (not (equals ent2creator ent1)) (game-entity-getattr ent2creator "vacuum"))
		    (game-entity-setattr ent1 "target" ent2creator)))))
	(if (not (string-equals (game-entity-getattr ent1 "team")
				(game-entity-getattr ent2 "team")))
	    (progn
	      '(let ((ent1xdir (game-entity-getattr ent1 "xdir"))
		     (ent1ydir (game-entity-getattr ent1 "ydir"))
		     (ent2xdir (game-entity-getattr ent2 "xdir"))
		     (ent2ydir (game-entity-getattr ent2 "ydir"))
		     (ent1mass (game-entity-getattr ent1 "mass"))
		     (ent2mass (game-entity-getattr ent2 "mass")))
		 (if (and ent1xdir ent1ydir ent1mass
			  ent2xdir ent2ydir ent2mass)
		     (progn
		       (setq ent1xdir (/ (* ent1xdir ent1mass) ent2mass))
		       (setq ent1ydir (/ (* ent1ydir ent1mass) ent2mass))
		       (setq ent2xdir (/ (* ent2xdir ent2mass) ent1mass))
		       (setq ent2ydir (/ (* ent2ydir ent2mass) ent1mass))
		       (game-entity-addvel ent1 ent2xdir ent2ydir)
		       (game-entity-addvel ent2 ent1xdir ent1ydir))))
	      (let ((dmg1 (game-entity-getattr ent2 "damage"))
		    (dmg2 (game-entity-getattr ent1 "damage")))
		(game-entity-damage ent1 dmg1)
		(game-entity-damage ent2 dmg2)))))))
