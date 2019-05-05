/**
 * This file stores the Transformer class which is the base class for every
 * Transformer that can apply continuous changes to Nodes.
 * @author barn
 * @version 20121027
 */
#ifndef __Transformer_HPP__
#define __Transformer_HPP__

/*===========================================================================*
 * INCLUDES base definition file for DLL import/export
 *===========================================================================*/

/*===========================================================================*
 * INCLUDES project headers
 *===========================================================================*/
#include "stdafx.h"
#include "Fadeable.hpp"

/*===========================================================================*
 * INCLUDES C/C++ standard library (and other external libraries)
 *===========================================================================*/

/*===========================================================================*
 * DEFINES and MACROS
 *===========================================================================*/

/*===========================================================================*
 * NAMESPACE, CONSTANTS and TYPE DECLARATIONS/IMPLEMENTATIONS
 *===========================================================================*/

namespace Trip
{

	/**
	 * The class Transformer provides an interface for appliyng continuous changes
	 * to Nodes.
	 *
	 * In general, you should not create the Transformers manually, but
	 * use the TransformerManager, that uses the Prototype pattern to create Transformers
	 * at runtime. Since you specify some prototypes of your Transformers for the Manager
	 * (that clones them when asked to create a new object), you have to take care
	 * that the copy constructor works the correct way. As long as you are not using raw pointers,
	 * or a shallow copy is sufficient, everything is fine. But when you are doing more complex stuff,
	 * and you need some complex members to be copied correctly, please implement an explicit copy constructor
	 * in your child class.
	 *
	 * When you create your own subclasses, you should override those 2 methods:
	 * apply() - applies the transformer on a target node;
	 * clone() - clones the current object in order to be used as a prototype for the TransformerManager.
	 *
	 * When you handle everything by the book, you only need to override apply() and clone().
	 * apply() shall do some arbitrary transformations on the node.
	 * However, if you have some initial or special instance vars that shall be copied at construction time,
	 * you have to override the copy constructor: Transformer( const Transformer&).
	 *
	 * When you have parameters that you want to be changeable by clients, use the _params vector
	 * also be aware of describing your parameters within the _param_descriptions vector.
	 */
	class Transformer : public Fadeable
	{
	private: // vars

		/// The name of this transformer.
		std::string _name;

		/**
		 * Spefifies, if this Transformer's influence and, if the value is 0, that it is disabled.
		 * Should be between 0 and 1 all the time.
		 */
		float _influence;

	protected: // vars

		/**
		 * Specifies the changeable params of the Transformer.
		 * Use it in your own subclasses in order to vary the Transformer's
		 * behaviour at runtime.
		 */
		std::vector<float> _params;

		/**
		 * Stores descriptions to the changeable params of the transformer.
		 * This way _param_descriptions[i] stores the description to _params[i].
		 * Use it in your own subclasses in order make the clients know about what each param means.
		 *
		 * TODO can it be more efficient?
		 */
		std::vector<String> _param_descriptions;

	public: // constructor

		/**
		 * Main constructor.
		 * Sets the Transformer initially enabled with an influence of 1.
		 */
		Transformer()
			: _name("<unnamed transformer>"),
			_influence(1)
		{}

		/**
		 * Destructor.
		 */
		~Transformer()
		{}


	public: // methods

		/**
		 * Applies the transform strategy once on the given Node.
		 * It takes the fade-in and fade-out parameters into account and
		 * calls the protected method apply() with adjusted influence values internally.
		 * Doesn't do anything if the TransformStrategy is not enabled.
		 * @param nd The Node on which to apply the strategy.
		 * @param tlc The time since the last frame rendered,
		 * multiply it in the implementations in order to keep the right timing.
		 * @param inf
		 * Specifies the influence of this strategy on the node and must be within [0,1].
		 * There is no guarantee that this will be checked.
		 * @param i
		 * A running variable that can be used to parameterize the strategy.
		 * E.g. it could be the number of the SceneNode in a List.
		 */
		void transform( Ogre::Node* nd, float tlc, uint i = 0);

		/**
		 * Clones the Transformer. Override this method in order to use prototypes of your own subclass.
		 */
		virtual Transformer* clone()
		{
			return new Transformer( *this);
		}

	public: // getters & setters

		/**
		 * This function sets the name of this particular Transformer.
		 * @param name The new name of the Transformer.
		 */
		void setName( String name)
		{
			_name = name;
		}


		/**
		 * Retrieves the name of this Transformer.
		 * @return The current name of this Transformer.
		 */
		const String& getName()
		{
			return _name;
		}


		/**
		 * Speficies the influence that this Transformer shall have.
		 * Should be a value within [0,1]. Higher/Lower values will be cut.
		 */
		void setInfluence( float f);


		/**
		 * Retrieves the stored influence.
		 * @return The influence value. Somewhere within [0,1].
		 */
		float getInfluence()
		{
			return _influence;
		}

		/**
		 * Retrieves the param vector from which you can
		 * read and write parameters in order to change the
		 * Transformer's behaviour by the client.
		 * Do not remove or add elements to this vector.
		 * @return A vector with all the parameters the Transformer bares.
		 *
		 * TODO make it safer (prohibit adding and removal of elements).
		 */
		std::vector<float>& getParams()
		{
			return _params;
		}

		/**
		 * Retrieves the desctription vector that corresponds the param vector.
		 * @return A vector of descriptions for the corresponding param vector.
		 * The i-th element in the returned vector is the description
		 * of the i-th element in the param vector.
		 * @see getParams()
		 */
		const std::vector<String>& getParamDescriptions()
		{
			return _param_descriptions;
		}

		/**
		 * Retrieves a reference to the i-th parameter of this transformer.
		 * You may change it.
		 * @param The index of the parameter in the parameter vector.
		 * @return The value of the specified parameter.
		 * @see getParams()
		 * @see getParamDescriptions()
		 */
		float& operator[]( unsigned int pos)
		{
			return _params.at(pos);
		}


	protected: // helpers

		/**
		 * Applies the transform strategy once on the given Node.
		 * @param nd The Node on which to apply the strategy.
		 * @param tlc The time since the last frame rendered,
		 * multiply it in the implementations in order to keep the right timing.
		 * @param i
		 * A running variable that can be used to parameterize the strategy.
		 * E.g. it could be the number of the SceneNode in a List.
		 * @param inf
		 * Specifies the influence of this strategy on the node and must be within [0,1].
		 * There is no guarantee that this will be checked.
		 */
		virtual void apply( Ogre::Node* nd, float tlc, uint i = 0, float inf = 1)
		{
			/* EMPTY IMPLEMENTATION */
		}

	}; // END class Transformer

} // END namespace Trip

#endif /* __Transformer_HPP__ */
