package com.sanguo.game.server.connectlogic.common.message.ProtoShop
{
	import laya.utils.Byte;
	public class CSPurchaseReq
	{
		public static const PROTO:String = "ProtoShop.CSPurchaseReq";
		public var package_root:*;
		public  var message:*;
		public var othuid:int;
		public var ud:int;
		public var propsid:int;
		public var propscnt:int;
		public var propsprice:int;
		public var sellflag:int;
		public var buyeruid:int;
		public var buyerfig:Byte;
		public var buyername:Byte;
		public function CSPurchaseReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			othuid = undefined;
			ud = undefined;
			propsid = undefined;
			propscnt = undefined;
			propsprice = undefined;
			sellflag = undefined;
			buyeruid = undefined;
			buyerfig = undefined;
			buyername = undefined;
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
			if(this.buyeruid!= undefined)
			{
				serializeObj.buyeruid = this.buyeruid;
			}
			if(this.buyerfig!= undefined)
			{
				serializeObj.buyerfig = this.buyerfig.getUint8Array(0, this.buyerfig.length);
				this.buyerfig.pos = 0;
			}
			if(this.buyername!= undefined)
			{
				serializeObj.buyername = this.buyername.getUint8Array(0, this.buyername.length);
				this.buyername.pos = 0;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):CSPurchaseReq
		{
			othuid = undefined;
			ud = undefined;
			propsid = undefined;
			propscnt = undefined;
			propsprice = undefined;
			sellflag = undefined;
			buyeruid = undefined;
			buyerfig = undefined;
			buyername = undefined;
			this.othuid = msgObj.othuid;
			this.ud = msgObj.ud;
			this.propsid = msgObj.propsid;
			this.propscnt = msgObj.propscnt;
			this.propsprice = msgObj.propsprice;
			this.sellflag = msgObj.sellflag;
			if(msgObj.hasOwnProperty("buyeruid"))
			{
				this.buyeruid = msgObj.buyeruid;
			}
			if(msgObj.hasOwnProperty("buyerfig"))
			{
				this.buyerfig = new Byte();
				this.buyerfig.writeArrayBuffer(msgObj.buyerfig);
				this.buyerfig.pos = 0;
			}
			if(msgObj.hasOwnProperty("buyername"))
			{
				this.buyername = new Byte();
				this.buyername.writeArrayBuffer(msgObj.buyername);
				this.buyername.pos = 0;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):CSPurchaseReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}