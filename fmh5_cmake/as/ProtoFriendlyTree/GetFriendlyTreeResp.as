package com.sanguo.game.server.connectlogic.common.message.ProtoFriendlyTree
{
	import laya.utils.Byte;
	public class GetFriendlyTreeResp
	{
		public static const PROTO:String = "ProtoFriendlyTree.GetFriendlyTreeResp";
		public var package_root:*;
		public  var message:*;
		public var basictreeinfo:Vector.<FriendlyTreeBasicCPP>;
		public var statustreeinfo:FriendlyTreeStatusCPP;
		public function GetFriendlyTreeResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			basictreeinfo = new Vector.<FriendlyTreeBasicCPP>();
			statustreeinfo = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.basictreeinfo = [];
			for(var i:int = 0;i < this.basictreeinfo.length;i++)
			{
				serializeObj.basictreeinfo.push(this.basictreeinfo[i].serialize());
			}
			serializeObj.statustreeinfo = this.statustreeinfo.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetFriendlyTreeResp
		{
			basictreeinfo = new Vector.<FriendlyTreeBasicCPP>();
			statustreeinfo = undefined;
			for(var i:int = 0;i < msgObj.basictreeinfo.length;i++)
			{
				this.basictreeinfo.push(new FriendlyTreeBasicCPP(package_root).unserialize(msgObj.basictreeinfo[i]));
			}
			this.statustreeinfo = new FriendlyTreeStatusCPP(package_root).unserialize(msgObj.statustreeinfo);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetFriendlyTreeResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}