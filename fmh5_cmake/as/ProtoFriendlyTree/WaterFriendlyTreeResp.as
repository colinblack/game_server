package com.sanguo.game.server.connectlogic.common.message.ProtoFriendlyTree
{
	import laya.utils.Byte;
	public class WaterFriendlyTreeResp
	{
		public static const PROTO:String = "ProtoFriendlyTree.WaterFriendlyTreeResp";
		public var package_root:*;
		public  var message:*;
		public var statustreeinfo:FriendlyTreeStatusCPP;
		public var curfriendlyvalue:int;
		public var basictreeinfo:FriendlyTreeBasicCPP;
		public var code:int;
		public function WaterFriendlyTreeResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			statustreeinfo = undefined;
			curfriendlyvalue = undefined;
			basictreeinfo = undefined;
			code = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			if(this.statustreeinfo!= undefined)
			{
				serializeObj.statustreeinfo = this.statustreeinfo.serialize();
			}
			if(this.curfriendlyvalue!= undefined)
			{
				serializeObj.curfriendlyvalue = this.curfriendlyvalue;
			}
			if(this.basictreeinfo!= undefined)
			{
				serializeObj.basictreeinfo = this.basictreeinfo.serialize();
			}
			serializeObj.code = this.code;
			return serializeObj;
		}
		public function unserialize(msgObj:*):WaterFriendlyTreeResp
		{
			statustreeinfo = undefined;
			curfriendlyvalue = undefined;
			basictreeinfo = undefined;
			code = undefined;
			if(msgObj.hasOwnProperty("statustreeinfo"))
			{
				this.statustreeinfo = new FriendlyTreeStatusCPP(package_root).unserialize(msgObj.statustreeinfo);
			}
			if(msgObj.hasOwnProperty("curfriendlyvalue"))
			{
				this.curfriendlyvalue = msgObj.curfriendlyvalue;
			}
			if(msgObj.hasOwnProperty("basictreeinfo"))
			{
				this.basictreeinfo = new FriendlyTreeBasicCPP(package_root).unserialize(msgObj.basictreeinfo);
			}
			this.code = msgObj.code;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):WaterFriendlyTreeResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}