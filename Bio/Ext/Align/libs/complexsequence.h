#ifndef DYNAMITEcomplexsequenceHEADERFILE
#define DYNAMITEcomplexsequenceHEADERFILE
#ifdef _cplusplus
extern "C" {
#endif
#include "sequence.h"
#include "probability.h" /* should move this to wisestring */


#define ComplexSequenceEvalSetLISTLENGTH 16

#define next_ComplexSequence_data(cs_struct,pointer) (pointer + cs_struct->depth)
#define ComplexSequence_data(cs,position,number)     (cs->data[cs->depth*position + number])



/* Object ComplexSequenceEval
 *
 * Descrip: This object is best left alone (!)
 *
 *        It represents a single way of mapping
 *        a sequence to some sort of number, eg
 *        amino acids to 0-25, bases to 0-4 or
 *        splice sites to log(Prob(splice))
 *
 *        This is handled by a reasonably scary
 *        pointer-to-function method
 *
 *        You'll use collections of them in 
 *        complexsequenceevalset's
 *
 *
 */
struct bp_sw_ComplexSequenceEval {  
    int dynamite_hard_link;  
    int type;    
    int sequence_type;   
    int left_window;     
    int right_window;    
    int left_lookback;   
    int outside_score;   
    void * data;     
    int data_type;  /* optional, to be used by eval_func to check things if it wants to */ 
    int (*eval_func)(int,void * ,char *);    
    } ;  
/* ComplexSequenceEval defined */ 
#ifndef DYNAMITE_DEFINED_ComplexSequenceEval
typedef struct bp_sw_ComplexSequenceEval bp_sw_ComplexSequenceEval;
#define ComplexSequenceEval bp_sw_ComplexSequenceEval
#define DYNAMITE_DEFINED_ComplexSequenceEval
#endif


/* Object ComplexSequenceEvalSet
 *
 * Descrip: This object holds a collection of 
 *        ComplexSequenceEval's. Its role is to
 *        define the sequence specific parts of a
 *        dynamic programming algorithm as computable
 *        functions. 
 *
 *        Ideally you should use pre-made ComplexSequenceEvalSets
 *        as it will save you alot of grief
 *
 *
 */
struct bp_sw_ComplexSequenceEvalSet {  
    int dynamite_hard_link;  
    int type;    
    boolean has_been_prepared;   
    int left_window;    /*  overall sequence eval  */ 
    int right_window;   /*  overall sequence eval */ 
    int left_lookback;  /*  overall sequence eval */ 
    ComplexSequenceEval ** cse;  
    int len;/* len for above cse  */ 
    int maxlen; /* maxlen for above cse */ 
    } ;  
/* ComplexSequenceEvalSet defined */ 
#ifndef DYNAMITE_DEFINED_ComplexSequenceEvalSet
typedef struct bp_sw_ComplexSequenceEvalSet bp_sw_ComplexSequenceEvalSet;
#define ComplexSequenceEvalSet bp_sw_ComplexSequenceEvalSet
#define DYNAMITE_DEFINED_ComplexSequenceEvalSet
#endif


/* Object ComplexSequence
 *
 * Descrip: A ComplexSequence is an abstraction of a 
 *        Sequence which can be handily made using
 *        ComplexSequenceEval functions and is efficiently
 *        laid out in memory.
 *
 *
 */
struct bp_sw_ComplexSequence {  
    int dynamite_hard_link;  
    int type;    
    Sequence * seq;  
    int * data;  
    int * datastore;     
    int depth;   
    int length;  
    } ;  
/* ComplexSequence defined */ 
#ifndef DYNAMITE_DEFINED_ComplexSequence
typedef struct bp_sw_ComplexSequence bp_sw_ComplexSequence;
#define ComplexSequence bp_sw_ComplexSequence
#define DYNAMITE_DEFINED_ComplexSequence
#endif




    /***************************************************/
    /* Callable functions                              */
    /* These are the functions you are expected to use */
    /***************************************************/



/* Function:  new_ComplexSequence(seq,cses)
 *
 * Descrip:    The basic way to make a ComplexSequence. Requires that
 *             you have already built a ComplexSequenceEvalSet (such as
 *             /default_aminoacid_ComplexSequenceEvalSet).
 *
 *
 *
 * Arg:         seq [UNKN ] Sequence that the ComplexSequence is based on [Sequence *]
 * Arg:        cses [UNKN ] EvalSet that defines the functions used on the sequence [ComplexSequenceEvalSet *]
 *
 * Return [UNKN ]  Undocumented return value [ComplexSequence *]
 *
 */
ComplexSequence * bp_sw_new_ComplexSequence(Sequence * seq,ComplexSequenceEvalSet * cses);
#define new_ComplexSequence bp_sw_new_ComplexSequence


/* Function:  show_ComplexSequence(cs,ofp)
 *
 * Descrip:    shows complex sequence in a vaguely
 *             human form
 *
 *
 * Arg:         cs [UNKN ] Undocumented argument [ComplexSequence *]
 * Arg:        ofp [UNKN ] Undocumented argument [FILE *]
 *
 */
void bp_sw_show_ComplexSequence(ComplexSequence * cs,FILE * ofp);
#define show_ComplexSequence bp_sw_show_ComplexSequence


/* Function:  prepare_ComplexSequenceEvalSet(cses)
 *
 * Descrip:    Calculates all the necessary offset for an EvalSet.
 *             This is necessary before using it in a /new_ComplexSequence
 *             place
 *
 *
 * Arg:        cses [UNKN ] Undocumented argument [ComplexSequenceEvalSet *]
 *
 * Return [UNKN ]  Undocumented return value [boolean]
 *
 */
boolean bp_sw_prepare_ComplexSequenceEvalSet(ComplexSequenceEvalSet * cses);
#define prepare_ComplexSequenceEvalSet bp_sw_prepare_ComplexSequenceEvalSet


/* Function:  can_evaluate_this_Sequence(cses,s)
 *
 * Descrip:    Checks that this ComplexSequenceEvalSet can be used with
 *             this Sequence. This is probably going to go defunct.
 *
 *
 *
 * Arg:        cses [UNKN ] Undocumented argument [ComplexSequenceEvalSet *]
 * Arg:           s [UNKN ] Undocumented argument [Sequence *]
 *
 * Return [UNKN ]  Undocumented return value [boolean]
 *
 */
boolean bp_sw_can_evaluate_this_Sequence(ComplexSequenceEvalSet * cses,Sequence * s);
#define can_evaluate_this_Sequence bp_sw_can_evaluate_this_Sequence


/* Function:  hard_link_ComplexSequenceEval(obj)
 *
 * Descrip:    Bumps up the reference count of the object
 *             Meaning that multiple pointers can 'own' it
 *
 *
 * Arg:        obj [UNKN ] Object to be hard linked [ComplexSequenceEval *]
 *
 * Return [UNKN ]  Undocumented return value [ComplexSequenceEval *]
 *
 */
ComplexSequenceEval * bp_sw_hard_link_ComplexSequenceEval(ComplexSequenceEval * obj);
#define hard_link_ComplexSequenceEval bp_sw_hard_link_ComplexSequenceEval


/* Function:  ComplexSequenceEval_alloc(void)
 *
 * Descrip:    Allocates structure: assigns defaults if given 
 *
 *
 *
 * Return [UNKN ]  Undocumented return value [ComplexSequenceEval *]
 *
 */
ComplexSequenceEval * bp_sw_ComplexSequenceEval_alloc(void);
#define ComplexSequenceEval_alloc bp_sw_ComplexSequenceEval_alloc


/* Function:  free_ComplexSequenceEval(obj)
 *
 * Descrip:    Free Function: removes the memory held by obj
 *             Will chain up to owned members and clear all lists
 *
 *
 * Arg:        obj [UNKN ] Object that is free'd [ComplexSequenceEval *]
 *
 * Return [UNKN ]  Undocumented return value [ComplexSequenceEval *]
 *
 */
ComplexSequenceEval * bp_sw_free_ComplexSequenceEval(ComplexSequenceEval * obj);
#define free_ComplexSequenceEval bp_sw_free_ComplexSequenceEval


/* Function:  add_ComplexSequenceEvalSet(obj,add)
 *
 * Descrip:    Adds another object to the list. It will expand the list if necessary
 *
 *
 * Arg:        obj [UNKN ] Object which contains the list [ComplexSequenceEvalSet *]
 * Arg:        add [OWNER] Object to add to the list [ComplexSequenceEval *]
 *
 * Return [UNKN ]  Undocumented return value [boolean]
 *
 */
boolean bp_sw_add_ComplexSequenceEvalSet(ComplexSequenceEvalSet * obj,ComplexSequenceEval * add);
#define add_ComplexSequenceEvalSet bp_sw_add_ComplexSequenceEvalSet


/* Function:  flush_ComplexSequenceEvalSet(obj)
 *
 * Descrip:    Frees the list elements, sets length to 0
 *             If you want to save some elements, use hard_link_xxx
 *             to protect them from being actually destroyed in the free
 *
 *
 * Arg:        obj [UNKN ] Object which contains the list  [ComplexSequenceEvalSet *]
 *
 * Return [UNKN ]  Undocumented return value [int]
 *
 */
int bp_sw_flush_ComplexSequenceEvalSet(ComplexSequenceEvalSet * obj);
#define flush_ComplexSequenceEvalSet bp_sw_flush_ComplexSequenceEvalSet


/* Function:  ComplexSequenceEvalSet_alloc_std(void)
 *
 * Descrip:    Equivalent to ComplexSequenceEvalSet_alloc_len(ComplexSequenceEvalSetLISTLENGTH)
 *
 *
 *
 * Return [UNKN ]  Undocumented return value [ComplexSequenceEvalSet *]
 *
 */
ComplexSequenceEvalSet * bp_sw_ComplexSequenceEvalSet_alloc_std(void);
#define ComplexSequenceEvalSet_alloc_std bp_sw_ComplexSequenceEvalSet_alloc_std


/* Function:  ComplexSequenceEvalSet_alloc_len(len)
 *
 * Descrip:    Allocates len length to all lists
 *
 *
 * Arg:        len [UNKN ] Length of lists to allocate [int]
 *
 * Return [UNKN ]  Undocumented return value [ComplexSequenceEvalSet *]
 *
 */
ComplexSequenceEvalSet * bp_sw_ComplexSequenceEvalSet_alloc_len(int len);
#define ComplexSequenceEvalSet_alloc_len bp_sw_ComplexSequenceEvalSet_alloc_len


/* Function:  hard_link_ComplexSequenceEvalSet(obj)
 *
 * Descrip:    Bumps up the reference count of the object
 *             Meaning that multiple pointers can 'own' it
 *
 *
 * Arg:        obj [UNKN ] Object to be hard linked [ComplexSequenceEvalSet *]
 *
 * Return [UNKN ]  Undocumented return value [ComplexSequenceEvalSet *]
 *
 */
ComplexSequenceEvalSet * bp_sw_hard_link_ComplexSequenceEvalSet(ComplexSequenceEvalSet * obj);
#define hard_link_ComplexSequenceEvalSet bp_sw_hard_link_ComplexSequenceEvalSet


/* Function:  ComplexSequenceEvalSet_alloc(void)
 *
 * Descrip:    Allocates structure: assigns defaults if given 
 *
 *
 *
 * Return [UNKN ]  Undocumented return value [ComplexSequenceEvalSet *]
 *
 */
ComplexSequenceEvalSet * bp_sw_ComplexSequenceEvalSet_alloc(void);
#define ComplexSequenceEvalSet_alloc bp_sw_ComplexSequenceEvalSet_alloc


/* Function:  free_ComplexSequenceEvalSet(obj)
 *
 * Descrip:    Free Function: removes the memory held by obj
 *             Will chain up to owned members and clear all lists
 *
 *
 * Arg:        obj [UNKN ] Object that is free'd [ComplexSequenceEvalSet *]
 *
 * Return [UNKN ]  Undocumented return value [ComplexSequenceEvalSet *]
 *
 */
ComplexSequenceEvalSet * bp_sw_free_ComplexSequenceEvalSet(ComplexSequenceEvalSet * obj);
#define free_ComplexSequenceEvalSet bp_sw_free_ComplexSequenceEvalSet


/* Function:  hard_link_ComplexSequence(obj)
 *
 * Descrip:    Bumps up the reference count of the object
 *             Meaning that multiple pointers can 'own' it
 *
 *
 * Arg:        obj [UNKN ] Object to be hard linked [ComplexSequence *]
 *
 * Return [UNKN ]  Undocumented return value [ComplexSequence *]
 *
 */
ComplexSequence * bp_sw_hard_link_ComplexSequence(ComplexSequence * obj);
#define hard_link_ComplexSequence bp_sw_hard_link_ComplexSequence


/* Function:  ComplexSequence_alloc(void)
 *
 * Descrip:    Allocates structure: assigns defaults if given 
 *
 *
 *
 * Return [UNKN ]  Undocumented return value [ComplexSequence *]
 *
 */
ComplexSequence * bp_sw_ComplexSequence_alloc(void);
#define ComplexSequence_alloc bp_sw_ComplexSequence_alloc


/* Function:  free_ComplexSequence(obj)
 *
 * Descrip:    Free Function: removes the memory held by obj
 *             Will chain up to owned members and clear all lists
 *
 *
 * Arg:        obj [UNKN ] Object that is free'd [ComplexSequence *]
 *
 * Return [UNKN ]  Undocumented return value [ComplexSequence *]
 *
 */
ComplexSequence * bp_sw_free_ComplexSequence(ComplexSequence * obj);
#define free_ComplexSequence bp_sw_free_ComplexSequence


  /* Unplaced functions */
  /* There has been no indication of the use of these functions */


    /***************************************************/
    /* Internal functions                              */
    /* you are not expected to have to call these      */
    /***************************************************/
int bp_sw_access_type_ComplexSequence(ComplexSequence * obj);
#define access_type_ComplexSequence bp_sw_access_type_ComplexSequence
boolean bp_sw_replace_type_ComplexSequenceEvalSet(ComplexSequenceEvalSet * obj,int type);
#define replace_type_ComplexSequenceEvalSet bp_sw_replace_type_ComplexSequenceEvalSet
int bp_sw_access_type_ComplexSequenceEvalSet(ComplexSequenceEvalSet * obj);
#define access_type_ComplexSequenceEvalSet bp_sw_access_type_ComplexSequenceEvalSet
boolean bp_sw_replace_has_been_prepared_ComplexSequenceEvalSet(ComplexSequenceEvalSet * obj,boolean has_been_prepared);
#define replace_has_been_prepared_ComplexSequenceEvalSet bp_sw_replace_has_been_prepared_ComplexSequenceEvalSet
boolean bp_sw_replace_type_ComplexSequence(ComplexSequence * obj,int type);
#define replace_type_ComplexSequence bp_sw_replace_type_ComplexSequence
boolean bp_sw_access_has_been_prepared_ComplexSequenceEvalSet(ComplexSequenceEvalSet * obj);
#define access_has_been_prepared_ComplexSequenceEvalSet bp_sw_access_has_been_prepared_ComplexSequenceEvalSet
Sequence * bp_sw_access_seq_ComplexSequence(ComplexSequence * obj);
#define access_seq_ComplexSequence bp_sw_access_seq_ComplexSequence
boolean bp_sw_replace_left_window_ComplexSequenceEvalSet(ComplexSequenceEvalSet * obj,int left_window);
#define replace_left_window_ComplexSequenceEvalSet bp_sw_replace_left_window_ComplexSequenceEvalSet
boolean bp_sw_replace_left_lookback_ComplexSequenceEvalSet(ComplexSequenceEvalSet * obj,int left_lookback);
#define replace_left_lookback_ComplexSequenceEvalSet bp_sw_replace_left_lookback_ComplexSequenceEvalSet
int bp_sw_access_left_window_ComplexSequenceEvalSet(ComplexSequenceEvalSet * obj);
#define access_left_window_ComplexSequenceEvalSet bp_sw_access_left_window_ComplexSequenceEvalSet
int bp_sw_access_left_lookback_ComplexSequenceEvalSet(ComplexSequenceEvalSet * obj);
#define access_left_lookback_ComplexSequenceEvalSet bp_sw_access_left_lookback_ComplexSequenceEvalSet
boolean bp_sw_replace_right_window_ComplexSequenceEvalSet(ComplexSequenceEvalSet * obj,int right_window);
#define replace_right_window_ComplexSequenceEvalSet bp_sw_replace_right_window_ComplexSequenceEvalSet
boolean bp_sw_replace_seq_ComplexSequence(ComplexSequence * obj,Sequence * seq);
#define replace_seq_ComplexSequence bp_sw_replace_seq_ComplexSequence
int bp_sw_access_right_window_ComplexSequenceEvalSet(ComplexSequenceEvalSet * obj);
#define access_right_window_ComplexSequenceEvalSet bp_sw_access_right_window_ComplexSequenceEvalSet
void bp_sw_show_one_position_ComplexSequence(ComplexSequence * cs,int pos,FILE * ofp);
#define show_one_position_ComplexSequence bp_sw_show_one_position_ComplexSequence
boolean bp_sw_can_evaluate_this_type(ComplexSequenceEvalSet * cses,int type);
#define can_evaluate_this_type bp_sw_can_evaluate_this_type
void bp_sw_swap_ComplexSequenceEvalSet(ComplexSequenceEval ** list,int i,int j) ;
#define swap_ComplexSequenceEvalSet bp_sw_swap_ComplexSequenceEvalSet
void bp_sw_qsort_ComplexSequenceEvalSet(ComplexSequenceEval ** list,int left,int right,int (*comp)(ComplexSequenceEval * ,ComplexSequenceEval * ));
#define qsort_ComplexSequenceEvalSet bp_sw_qsort_ComplexSequenceEvalSet
void bp_sw_sort_ComplexSequenceEvalSet(ComplexSequenceEvalSet * obj,int (*comp)(ComplexSequenceEval *, ComplexSequenceEval *));
#define sort_ComplexSequenceEvalSet bp_sw_sort_ComplexSequenceEvalSet
boolean bp_sw_expand_ComplexSequenceEvalSet(ComplexSequenceEvalSet * obj,int len);
#define expand_ComplexSequenceEvalSet bp_sw_expand_ComplexSequenceEvalSet

#ifdef _cplusplus
}
#endif

#endif
