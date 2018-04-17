(defun game-bounds-left () 0)
(defun game-bounds-right () 3650)
(defun game-bounds-up () 0)
(defun game-bounds-down () 2100)

(defun game-bounds-apply (ent)
  (let ((oob-left (< (game-entity-getattr ent "x") (game-bounds-left)))
	(oob-right (> (game-entity-getattr ent "x") (game-bounds-right)))
	(oob-up (< (game-entity-getattr ent "y") (game-bounds-up)))
	(oob-down (> (game-entity-getattr ent "y") (game-bounds-down))))
	
    (if (not (game-entity-getattr ent "bounds"))
	(game-entity-setattr ent "bounds" "die"))

    (if (string-equals (game-entity-getattr ent "bounds") "bounce")
	(progn
	  (game-bounds-block ent oob-left oob-right oob-up oob-down)
	  (game-bounds-bounce ent oob-left oob-right oob-up oob-down)))
    (if (string-equals (game-entity-getattr ent "bounds") "halt")
	(progn
	  (game-bounds-block ent oob-left oob-right oob-up oob-down)
	  (game-bounds-halt ent oob-left oob-right oob-up oob-down)))
    (if (string-equals (game-entity-getattr ent "bounds") "die")
	(progn
	  (game-bounds-kill ent oob-left oob-right oob-up oob-down)))))
(defun game-bounds-block (ent oob-left oob-right oob-up oob-down)
  (if oob-left (game-entity-setattr ent "x" (game-bounds-left)))
  (if oob-right (game-entity-setattr ent "x" (game-bounds-right)))
  (if oob-up (game-entity-setattr ent "y" (game-bounds-up)))
  (if oob-down (game-entity-setattr ent "y" (game-bounds-down))))

(defun game-bounds-halt (ent oob-left oob-right oob-up oob-down)
  (if (or oob-left oob-right oob-up oob-down)
      (progn
	(game-entity-setattr ent "xdir" 0)
	(game-entity-setattr ent "ydir" 0))))

(defun game-bounds-bounce (ent oob-left oob-right oob-up oob-down)
  (let ((xdir (game-entity-getattr ent "xdir"))
	(ydir (game-entity-getattr ent "ydir")))
    (if (or oob-left oob-right)
	(game-entity-setattr ent "xdir" (* -1 xdir)))
    (if (or oob-up oob-down)
	(game-entity-setattr ent "ydir" (* -1 ydir)))))

(defun game-bounds-kill (ent oob-left oob-right oob-up oob-down)
  (if (or oob-left oob-right oob-up oob-down) (game-entity-kill ent)))
