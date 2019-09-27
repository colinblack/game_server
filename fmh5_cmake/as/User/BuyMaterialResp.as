package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class BuyMaterialResp
	{
		public static const PROTO:String = "User.BuyMaterialResp";
		public var package_root:*;
		public  var message:*;
		public var commons:CommonItemsCPP;
		public var seq:int;
		public function BuyMaterialResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			commons = undefined;
			seq = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.commons = this.commons.serialize();
			serializeObj.seq = this.seq;
			return serializeObj;
		}
		public function unserialize(msgObj:*):BuyMaterialResp
		{
			commons = undefined;
			seq = undefined;
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			this.seq = msgObj.seq;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):BuyMaterialResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}