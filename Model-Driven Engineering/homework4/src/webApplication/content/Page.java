/**
 */
package webApplication.content;

import org.eclipse.emf.common.util.EList;

import webApplication.Named;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Page</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * </p>
 * <ul>
 *   <li>{@link webApplication.content.Page#getContents <em>Contents</em>}</li>
 *   <li>{@link webApplication.content.Page#getLinks <em>Links</em>}</li>
 *   <li>{@link webApplication.content.Page#getForms <em>Forms</em>}</li>
 * </ul>
 *
 * @see webApplication.content.ContentPackage#getPage()
 * @model
 * @generated
 */
public interface Page extends Named {
	/**
	 * Returns the value of the '<em><b>Contents</b></em>' containment reference list.
	 * The list contents are of type {@link webApplication.content.Content}.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Contents</em>' containment reference list isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Contents</em>' containment reference list.
	 * @see webApplication.content.ContentPackage#getPage_Contents()
	 * @model containment="true"
	 * @generated
	 */
	EList<Content> getContents();

	/**
	 * Returns the value of the '<em><b>Links</b></em>' containment reference list.
	 * The list contents are of type {@link webApplication.content.Link}.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Links</em>' containment reference list isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Links</em>' containment reference list.
	 * @see webApplication.content.ContentPackage#getPage_Links()
	 * @model containment="true"
	 * @generated
	 */
	EList<Link> getLinks();

	/**
	 * Returns the value of the '<em><b>Forms</b></em>' containment reference list.
	 * The list contents are of type {@link webApplication.content.Form}.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Forms</em>' containment reference list isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Forms</em>' containment reference list.
	 * @see webApplication.content.ContentPackage#getPage_Forms()
	 * @model containment="true"
	 * @generated
	 */
	EList<Form> getForms();

} // Page
