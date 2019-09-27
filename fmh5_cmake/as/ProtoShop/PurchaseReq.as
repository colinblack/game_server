package com.sanguo.game.server.connectlogic.common.message.ProtoShop
{
	import laya.utils.Byte;
	public class PurchaseReq
	{
		public static const PROTO:String = "ProtoShop.PurchaseReq";
		public var package_root:*;
		public  var message:*;
		public var othuid:int;
		public var ud:int;
		public var propsid:int;
		public var propscnt:int;
		public var propsprice:int;
		public var sellflag:int;
		public function PurchaseReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			othuid = undefined;
			ud = undefined;
			propsid = undefined;
			propscnt = undefined;
			propsprice = undefined;
			sellflag = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.othuid = this.othuid;
			serializeObj.ud = this.ud;
			serializeObj.propsid = this.propsid;
			serializeObj.propscnt = this.propscnt;
			serializeObj.propsprice = this.propsprice;
			serializeObj.sellflag = this.sellflag;
			return serializeObj;
		}
		public function unserialize(msgObj:*):PurchaseReq
		{
			othuid = undefined;
			ud = undefined;
			propsid = undefined;
			propscnt = undefined;
			propsprice = undefined;
			sellflag = undefined;
			this.othuid = msgObj.othuid;
			this.ud = msgObj.ud;
			this.propsid = msgObj.propsid;
			this.propscnt = msgObj.propscnt;
			this.propsprice = msgObj.propsprice;
			this.sellflag = msgObj.sellflag;
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