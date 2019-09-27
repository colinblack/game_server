package com.sanguo.game.server.connectlogic.common.message.ProtoShop
{
	import laya.utils.Byte;
	public class ShelfPropsReq
	{
		public static const PROTO:String = "ProtoShop.ShelfPropsReq";
		public var package_root:*;
		public  var message:*;
		public var ud:int;
		public var propsid:int;
		public var propscnt:int;
		public var propsprice:int;
		public var adflag:int;
		public function ShelfPropsReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			ud = undefined;
			propsid = undefined;
			propscnt = undefined;
			propsprice = undefined;
			adflag = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ud = this.ud;
			serializeObj.propsid = this.propsid;
			serializeObj.propscnt = this.propscnt;
			serializeObj.propsprice = this.propsprice;
			serializeObj.adflag = this.adflag;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ShelfPropsReq
		{
			ud = undefined;
			propsid = undefined;
			propscnt = undefined;
			propsprice = undefined;
			adflag = undefined;
			this.ud = msgObj.ud;
			this.propsid = msgObj.propsid;
			this.propscnt = msgObj.propscnt;
			this.propsprice = msgObj.propsprice;
			this.adflag = msgObj.adflag;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ShelfPropsReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}