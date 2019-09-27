package com.sanguo.game.server.connectlogic.common.message.ProtoShop
{
	import laya.utils.Byte;
	public class ShopCPP
	{
		public static const PROTO:String = "ProtoShop.ShopCPP";
		public var package_root:*;
		public  var message:*;
		public var ud:int;
		public var propsid:int;
		public var propscnt:int;
		public var propsprice:int;
		public var adflag:int;
		public var sellflag:int;
		public var buyerfig:Byte;
		public var buyername:Byte;
		public var vipshelfflag:int;
		public var buyeruid:int;
		public function ShopCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			ud = undefined;
			propsid = undefined;
			propscnt = undefined;
			propsprice = undefined;
			adflag = undefined;
			sellflag = undefined;
			buyerfig = undefined;
			buyername = undefined;
			vipshelfflag = undefined;
			buyeruid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ud = this.ud;
			serializeObj.propsid = this.propsid;
			serializeObj.propscnt = this.propscnt;
			serializeObj.propsprice = this.propsprice;
			serializeObj.adflag = this.adflag;
			serializeObj.sellflag = this.sellflag;
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
			serializeObj.vipshelfflag = this.vipshelfflag;
			if(this.buyeruid!= undefined)
			{
				serializeObj.buyeruid = this.buyeruid;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ShopCPP
		{
			ud = undefined;
			propsid = undefined;
			propscnt = undefined;
			propsprice = undefined;
			adflag = undefined;
			sellflag = undefined;
			buyerfig = undefined;
			buyername = undefined;
			vipshelfflag = undefined;
			buyeruid = undefined;
			this.ud = msgObj.ud;
			this.propsid = msgObj.propsid;
			this.propscnt = msgObj.propscnt;
			this.propsprice = msgObj.propsprice;
			this.adflag = msgObj.adflag;
			this.sellflag = msgObj.sellflag;
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
			this.vipshelfflag = msgObj.vipshelfflag;
			if(msgObj.hasOwnProperty("buyeruid"))
			{
				this.buyeruid = msgObj.buyeruid;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ShopCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}