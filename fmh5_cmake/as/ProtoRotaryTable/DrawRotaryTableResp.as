package com.sanguo.game.server.connectlogic.common.message.ProtoRotaryTable
{
	import laya.utils.Byte;
	public class DrawRotaryTableResp
	{
		public static const PROTO:String = "ProtoRotaryTable.DrawRotaryTableResp";
		public var package_root:*;
		public  var message:*;
		public var gridid:int;
		public var commons:CommonItemsCPP;
		public var drawinfo:DrawCntCPP;
		public var curfriendlyvalue:int;
		public function DrawRotaryTableResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			gridid = undefined;
			commons = undefined;
			drawinfo = undefined;
			curfriendlyvalue = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.gridid = this.gridid;
			serializeObj.commons = this.commons.serialize();
			serializeObj.drawinfo = this.drawinfo.serialize();
			serializeObj.curfriendlyvalue = this.curfriendlyvalue;
			return serializeObj;
		}
		public function unserialize(msgObj:*):DrawRotaryTableResp
		{
			gridid = undefined;
			commons = undefined;
			drawinfo = undefined;
			curfriendlyvalue = undefined;
			this.gridid = msgObj.gridid;
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			this.drawinfo = new DrawCntCPP(package_root).unserialize(msgObj.drawinfo);
			this.curfriendlyvalue = msgObj.curfriendlyvalue;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):DrawRotaryTableResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}