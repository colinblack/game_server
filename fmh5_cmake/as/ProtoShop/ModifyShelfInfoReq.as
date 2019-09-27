package com.sanguo.game.server.connectlogic.common.message.ProtoShop
{
	import laya.utils.Byte;
	public class ModifyShelfInfoReq
	{
		public static const PROTO:String = "ProtoShop.ModifyShelfInfoReq";
		public var package_root:*;
		public  var message:*;
		public var ud:int;
		public var flag:int;
		public function ModifyShelfInfoReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			ud = undefined;
			flag = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ud = this.ud;
			serializeObj.flag = this.flag;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ModifyShelfInfoReq
		{
			ud = undefined;
			flag = undefined;
			this.ud = msgObj.ud;
			this.flag = msgObj.flag;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ModifyShelfInfoReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}