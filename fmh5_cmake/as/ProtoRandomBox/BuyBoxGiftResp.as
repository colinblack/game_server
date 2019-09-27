package com.sanguo.game.server.connectlogic.common.message.ProtoRandomBox
{
	import laya.utils.Byte;
	public class BuyBoxGiftResp
	{
		public static const PROTO:String = "ProtoRandomBox.BuyBoxGiftResp";
		public var package_root:*;
		public  var message:*;
		public var commons:CommonItemsCPP;
		public function BuyBoxGiftResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.commons = this.commons.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):BuyBoxGiftResp
		{
			commons = undefined;
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):BuyBoxGiftResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}