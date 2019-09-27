package com.sanguo.game.server.connectlogic.common.message.ProtoNPCUser
{
	import laya.utils.Byte;
	public class NPCShopCPP
	{
		public static const PROTO:String = "ProtoNPCUser.NPCShopCPP";
		public var package_root:*;
		public  var message:*;
		public var ud:int;
		public var propsid:int;
		public var propscnt:int;
		public var sellflag:int;
		public function NPCShopCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			ud = undefined;
			propsid = undefined;
			propscnt = undefined;
			sellflag = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ud = this.ud;
			serializeObj.propsid = this.propsid;
			serializeObj.propscnt = this.propscnt;
			serializeObj.sellflag = this.sellflag;
			return serializeObj;
		}
		public function unserialize(msgObj:*):NPCShopCPP
		{
			ud = undefined;
			propsid = undefined;
			propscnt = undefined;
			sellflag = undefined;
			this.ud = msgObj.ud;
			this.propsid = msgObj.propsid;
			this.propscnt = msgObj.propscnt;
			this.sellflag = msgObj.sellflag;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):NPCShopCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}