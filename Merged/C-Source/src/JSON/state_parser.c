#ifndef		__JSON_STATE_PARSER_C__
# define	__JSON_STATE_PARSER_C__

# include	"JSONParser.h"

/*
** Set the name variables depending on the state. ONly the state that aren't linked to a token. (Separator, assignement, etc..)
*/
void		JSONstate_non_token_fragment(char **tokens, JSONtree_parser *info, int *i, message *msg)
{
  if ((*info).current_state == ESNAME || (*info).last_state == DECLARATIONB)
    (*info).elem_name = strdup(tokens[*i]);
  if ((*info).last_state == ASSIGNEMENT || (*info).last_state == TYPETOKENB || (*info).current_state == VALUE || \
      ((*info).last_state == SEPARATOR && msg->segment->type == STAB))
    {
      JSONidentify_token_type(tokens[((*info).last_state == TYPETOKENB) ? *i + 1 : *i], info);
      (*info).content = strdup(tokens[*i]);
    }
}

/*
** Set the name variables depending on the state. ONly the state that are linked to a token. (Separator, assignement, etc..)
*/
void		JSONstate_token_fragment(const char *fragment, JSONtree_parser *info, message *msg)
{
  if ((*info).last_state == DECLARATIONB && fragment[0] != '\"') // If the state is a declaration (Element or Segment) and the current char isn't a quote.
    {
      // (*info).XXX is equal to info->XXX but it's quicker.
      (*info).current_state = ESNAME;
      return ;
    }
  if ((*info).last_state == TYPETOKENB && fragment[0] != '\"') // If the state is the begining of a content.
    {
      // (*info).XXX is equal to info->XXX but it's quicker.
      (*info).current_state = VALUE;
      return ;
    }
  switch (fragment[0]) {
  case ':': // Parse for a doube dot token character.
    // (*info).XXX is equal to info->XXX but it's quicker.
    (*info).current_state = ASSIGNEMENT;
    break ;
  case '\"': // Parse for a doube quote token character.
    if ((*info).last_state == DECLARATIONB) //if the last time it was a declaration then it's obviously a segment or an element without a name.
      { // DECLARATIONB(for begin) then DELCARATIONE (for end).
	if ((*info).elem_name == NULL)
	  (*info).elem_name = strdup("");
	(*info).current_state = DECLARATIONE;
      }
    if ((*info).last_state == TYPETOKENB) // if the last time it was the begining of a content then it's empty. Plus it's an empty string.
      {
	if ((*info).content == NULL)
	  (*info).content = strdup("");
	(*info).current_state = TYPETOKENE;
	(*info).current_tree_type = ATTRIBUT;
	(*info).value_type = STRING;
      }
    if ((*info).last_state == ESNAME) // If the last time it was the name of an element or a segment then it's the end of the declaration.
      (*info).current_state = DECLARATIONE;
    if ((*info).last_state == LISTB || (*info).last_state == LISTE) // if the last time it was list declaration or a list end declaration then it must be a Declaration to follow.
      (*info).current_state = DECLARATIONB;
    if ((*info).last_state == SEPARATOR) // If the last time it was a separation ( , )
      {
	if (msg->segment != NULL && msg->segment->type == STAB)
	  (*info).current_state = TYPETOKENB;
	else
	  (*info).current_state = DECLARATIONB;
      }
    if ((*info).last_state == ASSIGNEMENT || (*info).last_state == TABB) // if the last time it was an assignement or the begining of an array, then it must be the beging of a value.
      (*info).current_state = TYPETOKENB;
    if ((*info).last_state == VALUE) // if it was a value before the nit must be the end of it. (a string certainly)
      (*info).current_state = TYPETOKENE;
    break ;
  case '[': // Parse for openning bracket token character.
    if ((*info).last_state == ASSIGNEMENT || (*info).last_state == TABB || (*info).last_state == NONE || \
	((*info).last_state == SEPARATOR && msg->segment != NULL && msg->segment->type == STAB)) // If the last time it was :
      // either an assignement (:) or another openning bracket ([) or nothing (the begining) or a separator (,) and there is at least a segment and it's an array.
      { // Then it's an array obviously.
	(*info).current_state = TABB;
	(*info).current_tree_type = TAB;
      }
    else
      (*info).current_state = ERROR;
    break ;
  case ']': // Parse for closing bracket
    if ((*info).last_state == ASSIGNEMENT)
      (*info).current_state = ERROR;
    (*info).current_state = TABE;
    (*info).current_tree_type = CLOSEGROUP;
    break ;
  case '{': // parse for openning braces
    if ((*info).last_state == TABB || ((*info).last_state == SEPARATOR && (*info).is_in_tab != 0) || \
	(*info).last_state == NONE || (*info).last_state == ASSIGNEMENT || (*info).last_state == SEPARATOR)
      { // Every condition to let it be a list beging.
	(*info).current_state = LISTB;
	(*info).current_tree_type = LIST;
      }
    else
      (*info).current_state = ERROR;
    break ;
  case '}': // parse for closing braces
    if ((*info).last_state == ASSIGNEMENT)
      (*info).current_state = ERROR;
    if ((*info).last_state == VALUE || (*info).last_state == TABE ||	\
	(*info).last_state == LISTE || (*info).last_state == TYPETOKENE || \
	(*info).last_state == LISTB)
      {// Every condition to let it be a list closing.
	(*info).current_state = LISTE;
	(*info).current_tree_type = CLOSEGROUP;
      }
    break ;
  case ',': // Parse for a separator token
    if ((*info).last_state == VALUE || (*info).last_state == TYPETOKENE || (*info).last_state == TABE || \
	(*info).last_state == LISTE ||(*info).last_state == SEPARATOR)
      (*info).current_state = SEPARATOR;
    else
      (*info).current_state = ERROR;
    if ((*info).last_state == SEPARATOR)
      (*info).current_tree_type = ELEMENT;
    break ;
  }
}

#endif		/* __JSON_STATE_PARSER_C__ */
