package com.sanguo.game.server.connectlogic.common.message.ProtoShipping
{
	import laya.utils.Byte;
	public class CSOfferAidResp
	{
		public static const PROTO:String = "ProtoShipping.CSOfferAidResp";
		public var package_root:*;
		public  var message:*;
		public var myuid:int;
		public function CSOfferAidResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			myuid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.myuid = this.myuid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):CSOfferAidResp
		{
			myuid = undefined;
			this.myuid = msgObj.myuid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):CSOfferAidResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}