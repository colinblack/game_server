package com.sanguo.game.server.connectlogic.common.message.ProtoProduce
{
	import laya.utils.Byte;
	public class CSOfferHelpResp
	{
		public static const PROTO:String = "ProtoProduce.CSOfferHelpResp";
		public var package_root:*;
		public  var message:*;
		public var myuid:int;
		public var othuid:int;
		public var othfruit:FruitCPP;
		public function CSOfferHelpResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			myuid = undefined;
			othuid = undefined;
			othfruit = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.myuid = this.myuid;
			serializeObj.othuid = this.othuid;
			serializeObj.othfruit = this.othfruit.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):CSOfferHelpResp
		{
			myuid = undefined;
			othuid = undefined;
			othfruit = undefined;
			this.myuid = msgObj.myuid;
			this.othuid = msgObj.othuid;
			this.othfruit = new FruitCPP(package_root).unserialize(msgObj.othfruit);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):CSOfferHelpResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}