package com.sanguo.game.server.connectlogic.common.message.ProtoProduce
{
	import laya.utils.Byte;
	public class OfferHelpResp
	{
		public static const PROTO:String = "ProtoProduce.OfferHelpResp";
		public var package_root:*;
		public  var message:*;
		public var othuid:int;
		public var othfruit:FruitCPP;
		public var commons:CommonItemsCPP;
		public function OfferHelpResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			othuid = undefined;
			othfruit = undefined;
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.othuid = this.othuid;
			serializeObj.othfruit = this.othfruit.serialize();
			serializeObj.commons = this.commons.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):OfferHelpResp
		{
			othuid = undefined;
			othfruit = undefined;
			commons = undefined;
			this.othuid = msgObj.othuid;
			this.othfruit = new FruitCPP(package_root).unserialize(msgObj.othfruit);
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):OfferHelpResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}