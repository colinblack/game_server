package com.sanguo.game.server.connectlogic.common.message.ProtoShipping
{
	import laya.utils.Byte;
	public class OfferAidReq
	{
		public static const PROTO:String = "ProtoShipping.OfferAidReq";
		public var package_root:*;
		public  var message:*;
		public var othuid:int;
		public var boxid:int;
		public var propsid:int;
		public var propscnt:int;
		public var coin:int;
		public var exp:int;
		public function OfferAidReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			othuid = undefined;
			boxid = undefined;
			propsid = undefined;
			propscnt = undefined;
			coin = undefined;
			exp = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.othuid = this.othuid;
			serializeObj.boxid = this.boxid;
			serializeObj.propsid = this.propsid;
			serializeObj.propscnt = this.propscnt;
			serializeObj.coin = this.coin;
			serializeObj.exp = this.exp;
			return serializeObj;
		}
		public function unserialize(msgObj:*):OfferAidReq
		{
			othuid = undefined;
			boxid = undefined;
			propsid = undefined;
			propscnt = undefined;
			coin = undefined;
			exp = undefined;
			this.othuid = msgObj.othuid;
			this.boxid = msgObj.boxid;
			this.propsid = msgObj.propsid;
			this.propscnt = msgObj.propscnt;
			this.coin = msgObj.coin;
			this.exp = msgObj.exp;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):OfferAidReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}