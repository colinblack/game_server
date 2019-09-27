package com.sanguo.game.server.connectlogic.common.message.ProtoNPCUser
{
	import laya.utils.Byte;
	public class PurchaseReq
	{
		public static const PROTO:String = "ProtoNPCUser.PurchaseReq";
		public var package_root:*;
		public  var message:*;
		public var ud:int;
		public function PurchaseReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			ud = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ud = this.ud;
			return serializeObj;
		}
		public function unserialize(msgObj:*):PurchaseReq
		{
			ud = undefined;
			this.ud = msgObj.ud;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):PurchaseReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}