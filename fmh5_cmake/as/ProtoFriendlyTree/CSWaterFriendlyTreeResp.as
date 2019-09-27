package com.sanguo.game.server.connectlogic.common.message.ProtoFriendlyTree
{
	import laya.utils.Byte;
	public class CSWaterFriendlyTreeResp
	{
		public static const PROTO:String = "ProtoFriendlyTree.CSWaterFriendlyTreeResp";
		public var package_root:*;
		public  var message:*;
		public var myuid:int;
		public var statustreeinfo:FriendlyTreeStatusCPP;
		public var basictreeinfo:FriendlyTreeBasicCPP;
		public var code:int;
		public function CSWaterFriendlyTreeResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			myuid = undefined;
			statustreeinfo = undefined;
			basictreeinfo = undefined;
			code = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			if(this.myuid!= undefined)
			{
				serializeObj.myuid = this.myuid;
			}
			if(this.statustreeinfo!= undefined)
			{
				serializeObj.statustreeinfo = this.statustreeinfo.serialize();
			}
			if(this.basictreeinfo!= undefined)
			{
				serializeObj.basictreeinfo = this.basictreeinfo.serialize();
			}
			serializeObj.code = this.code;
			return serializeObj;
		}
		public function unserialize(msgObj:*):CSWaterFriendlyTreeResp
		{
			myuid = undefined;
			statustreeinfo = undefined;
			basictreeinfo = undefined;
			code = undefined;
			if(msgObj.hasOwnProperty("myuid"))
			{
				this.myuid = msgObj.myuid;
			}
			if(msgObj.hasOwnProperty("statustreeinfo"))
			{
				this.statustreeinfo = new FriendlyTreeStatusCPP(package_root).unserialize(msgObj.statustreeinfo);
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
		public function decode(buffer:*):CSWaterFriendlyTreeResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}